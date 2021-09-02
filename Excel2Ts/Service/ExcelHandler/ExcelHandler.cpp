#include "ExcelHandler.h"

ExcelHandler::ExcelHandler(QObject *parent)
    : QObject(parent),
      m_filePath(),
      m_excelRW(new ExcelReadWrite(this)),
      m_fileFormat(TWO_COLUMNS),
      m_translationBlockList(),
      m_translationBlock()
{
    qRegisterMetaType<ExcelHandler::HANDLE_ERROR>("ExcelHandler::HANDLE_ERROR");
}

void ExcelHandler::setFilePath(QString filePath)
{
    m_filePath = filePath;
    m_excelRW->openFile(m_filePath);
}

ExcelHandler::HANDLE_ERROR ExcelHandler::handleFile()
{
    int rowCount         = m_excelRW->getRows();
    int columnCount      = m_excelRW->getColumns();
    int rowStartIndex    = m_excelRW->getStartRows();
    int columnStartIndex = m_excelRW->getStartColumns();

    ExcelHandler::HANDLE_ERROR handleResult = NORMAL;

    QString className   = "";
    QString srcText     = "";
    QString translation = "";
    TranslationBlock translationBlock;

    if (m_excelRW == NULL)
        m_excelRW = new ExcelReadWrite();

    if (!m_excelRW->openFile(m_filePath)) {
        handleResult = OPEN_FILE_FAILED;
        goto errorFinished;
    }

    m_excelRW->setCurrentWorkSheet(1);

    /*
     * 格式分为2种：2列与3列；
     * 2列的格式如下：
     * 源文 | 译文
     * src | translation
     *
     * 3列的格式如下：
     * 类名 | 源文 | 译文
     * xxx | src | translation
     *     | src | translation
     */
    if (rowStartIndex > 1 || columnStartIndex > 1) {
        handleResult = FORMAT_ERROR;
        goto errorFinished;
    }

    if (m_fileFormat == TWO_COLUMNS) {
        if (columnCount != TWO_COLUMNS)
            goto formatError;
    }
    else {
        if (columnCount != THREE_COLUMNS)
            goto formatError;
    }

    for (int i = rowStartIndex; i <= rowCount; i++) {
        switch (m_fileFormat) {
        case THREE_COLUMNS:
            className   = m_excelRW->getCellText(i, 1);
            srcText     = m_excelRW->getCellText(i, 2);
            translation = m_excelRW->getCellText(i, 3);

            if (className.isEmpty()) {
                if (!m_translationBlock.addMap(srcText, translation)) {
                    handleResult = REPEAT_KEY;
                    goto errorFinished;
                }
            }
            else {
                if (m_translationBlock.className().isEmpty()) {
                    if (m_translationBlock.addMap(srcText, translation)) {
                        handleResult = REPEAT_KEY;
                        goto errorFinished;
                    }
                }
                else {
                    //查找是否已经存在这个类的记录
                    int index = this->blockListIndexOf(className);
                    if (index != -1) {
                        //存在则直接拿出这个记录，进行追加记录
                        m_translationBlock = m_translationBlockList.at(index);
                        m_translationBlockList.removeAt(index);
                    }
                    else {
                        //不存在则先把原来的添加到list中，然后清空中间变量，准备记录新的类
                        m_translationBlockList.append(m_translationBlock);
                        m_translationBlock.clear();
                        m_translationBlock.setClassName(className);
                    }

                    if (!m_translationBlock.addMap(srcText, translation)) {
                        handleResult = REPEAT_KEY;
                        goto errorFinished;
                    }
                }
            }

            break;

        case TWO_COLUMNS:
        default:
            srcText     = m_excelRW->getCellText(i, 1);
            translation = m_excelRW->getCellText(i, 2);
            if (!m_translationBlock.addMap(srcText, translation)) {
                handleResult = REPEAT_KEY;
                goto errorFinished;
            }
            break;
        }
    }

    if (m_fileFormat == TWO_COLUMNS)
        m_translationBlockList.append(m_translationBlock);

formatError:
    handleResult = FORMAT_ERROR;

errorFinished:
    if (m_excelRW != NULL) {
        delete m_excelRW;
        m_excelRW = NULL;
    }

    return handleResult;
}

QString ExcelHandler::getTranslation(const QString className, const QString srcText)
{
    foreach (TranslationBlock each, m_translationBlockList) {
        if (className == each.className())
            return m_translationBlock.translationMap().value(srcText);
    }
}

QString ExcelHandler::getTranslation(const QString srcText)
{
    QMap<QString, QString> mapper = m_translationBlock.translationMap();
    return m_translationBlock.translationMap().value(srcText);
}

ExcelHandler::FILE_FORMAT ExcelHandler::getFileFormat() const
{
    return m_fileFormat;
}

void ExcelHandler::setFileFormat(const FILE_FORMAT &fileFormat)
{
    m_fileFormat = fileFormat;
}

int ExcelHandler::blockListIndexOf(const QString className)
{
    for (int i = 0; i < m_translationBlockList.count(); i++) {
        if (m_translationBlock.className() == className)
            return i;
    }

    return -1;
}
