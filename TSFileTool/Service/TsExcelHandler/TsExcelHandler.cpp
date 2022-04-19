#include "TsExcelHandler.h"

TsExcelHandler::TsExcelHandler(QObject *parent)
    : QObject(parent),
      m_filePath(),
//      m_excelRW(new AXOBJECT::ExcelReadWrite(this)),
      m_excelRW(new XLSX::ExcelReadWriter(this)),
      m_fileFormat(TWO_COLUMNS),
      m_translationBlockList(),
      m_translationBlock()
{
    qRegisterMetaType<TsExcelHandler::HANDLE_ERROR>("ExcelHandler::HANDLE_ERROR");
}

void TsExcelHandler::setFilePath(QString filePath)
{
    m_filePath = filePath;
}

void TsExcelHandler::closeFile()
{
    m_filePath = "";
    m_excelRW->save();
}

TsExcelHandler::HANDLE_ERROR TsExcelHandler::handleTranslation()
{
    int rowCount         = m_excelRW->getRowCount();
    int columnCount      = m_excelRW->getColumnCount();
    int rowStartIndex    = m_excelRW->getFirstRow();
    int columnStartIndex = m_excelRW->getFirstColumn();

    TsExcelHandler::HANDLE_ERROR handleResult = NORMAL;

    QString className   = "";
    QString srcText     = "";
    QString translation = "";
    TranslationBlock translationBlock;

    if (m_excelRW == NULL) {
//        m_excelRW = new AXOBJECT::ExcelReadWrite();
        m_excelRW = new XLSX::ExcelReadWriter(this);
    }

    if (!m_excelRW->openFile(m_filePath)) {
        handleResult = OPEN_FILE_FAILED;
        goto normalFinished;
    }

//    m_excelRW->setCurrentWorkSheet(1);

    /*
     * 格式分为2种：2列与3列；
     * 2列的格式如下：
     * 源文 | 译文
     * src | translation
     *
     * 3列的格式如下：
     * 字段名 | 源文 | 译文
     * xxx | src | translation
     *     | src | translation
     */
    if (rowStartIndex > 1 || columnStartIndex > 1) {
        handleResult = FORMAT_ERROR;
        goto normalFinished;
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
            className   = m_excelRW->getCellText(i, 1).toString();
            srcText     = m_excelRW->getCellText(i, 2).toString();
            translation = m_excelRW->getCellText(i, 3).toString();

            if (className.isEmpty()) {
                if (!m_translationBlock.addMap(srcText, translation))
                    goto repeatKey;
            }
            else {
                if (m_translationBlock.field().isEmpty()) {
                    if (m_translationBlock.addMap(srcText, translation))
                        goto repeatKey;
                }
                else {
                    //查找是否已经存在这个字段的记录
                    int index = this->blockListIndexOf(className);
                    if (index != -1) {
                        //存在则直接拿出这个记录，进行追加记录
                        m_translationBlock = m_translationBlockList.at(index);
                        m_translationBlockList.removeAt(index);
                    }
                    else {
                        //不存在则先把原来的添加到list中，然后清空中间变量，准备记录新的字段
                        m_translationBlockList.append(m_translationBlock);
                        m_translationBlock.clear();
                        m_translationBlock.setField(className);
                    }

                    if (!m_translationBlock.addMap(srcText, translation))
                        goto repeatKey;
                }
            }
            break;

        case TWO_COLUMNS:
        default:
            srcText     = m_excelRW->getCellText(i, 1).toString();
            translation = m_excelRW->getCellText(i, 2).toString();
            if (!m_translationBlock.addMap(srcText, translation))
//                goto repeatKey;

            break;
        }
    }

    if (m_fileFormat == TWO_COLUMNS)
        m_translationBlockList.append(m_translationBlock);

    goto normalFinished;

formatError:
    handleResult = FORMAT_ERROR;
    goto normalFinished;

repeatKey:
    handleResult = REPEAT_KEY;

normalFinished:
    return handleResult;
}

bool TsExcelHandler::setOutputExcelFile(const QString filePath)
{
    QFile file(filePath);
    bool result = false;

    if (!file.exists()) {
        result = file.open(QIODevice::WriteOnly);
        file.close();
    }

    if (result)
        return m_excelRW->openFile(filePath);

    return false;
}

bool TsExcelHandler::writeCell(const QString text, const int row, const int column, QXlsx::Format format)
{
    if (m_excelRW->getFilePath().isEmpty())
        m_excelRW->openFile(m_filePath);

    return m_excelRW->setCellText(row, column, text, format);
}

QString TsExcelHandler::getTranslation(const QString field, const QString srcText)
{
    foreach (TranslationBlock each, m_translationBlockList) {
        if (field == each.field())
            return m_translationBlock.translationMap().value(srcText);
    }

    return "";
}

QString TsExcelHandler::getTranslation(const QString srcText)
{
    QMap<QString, QString> mapper = m_translationBlock.translationMap();
    return m_translationBlock.translationMap().value(srcText);
}

TsExcelHandler::FILE_FORMAT TsExcelHandler::getFileFormat() const
{
    return m_fileFormat;
}

void TsExcelHandler::setFileFormat(const FILE_FORMAT &fileFormat)
{
    m_fileFormat = fileFormat;
}

bool TsExcelHandler::mergeCells(const int firstRow, const int firstColumn, const int lastRow, const int lastColumn)
{
    return m_excelRW->mergeCells(firstRow, firstColumn, lastRow, lastColumn);
}

int TsExcelHandler::blockListIndexOf(const QString className)
{
    for (int i = 0; i < m_translationBlockList.count(); i++) {
        if (m_translationBlock.field() == className)
            return i;
    }

    return -1;
}
