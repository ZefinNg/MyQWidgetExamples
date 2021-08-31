#include "ExcelHandler.h"

ExcelHandler::ExcelHandler(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<ExcelHandler::HANDLE_ERROR>("ExcelHandler::HANDLE_ERROR");

    m_filePath = "";
    m_excelRW  = NULL;

    m_translationMapper.clear();
}

void ExcelHandler::setFilePath(QString filePath)
{
    m_filePath = filePath;

    this->start();
}

void ExcelHandler::run()
{
    if (m_excelRW == NULL)
        m_excelRW = new ExcelReadWrite();

    if (!m_excelRW->openFile(m_filePath))
        emit errorOccur(ExcelHandler::OPEN_FILE_FAILED);

    m_excelRW->setCurrentWorkSheet(1);

    int rowCount         = m_excelRW->getRows();
    int columnCount      = m_excelRW->getColumns();
    int rowStartIndex    = m_excelRW->getStartRows();
    int columnStartIndex = m_excelRW->getStartColumns();

    QString srcText, translation;

    /* 检查格式是否正确：
     * 源文 | 译文
     * src | translation
     */
    if (columnCount != 2 || rowStartIndex > 1 || columnStartIndex > 1) {
        emit errorOccur(FORMAT_ERROR);
        goto normalFinished;
    }

    for (int i = rowStartIndex; i <= rowCount; i++) {
        srcText     = m_excelRW->getCellText(i, 1);
        translation = m_excelRW->getCellText(i, 2);

        if (m_translationMapper.contains(srcText)) {
            emit errorOccur(ExcelHandler::REPEAT_KEY);
            goto normalFinished;
        }
        else
            m_translationMapper.insert(srcText, translation);
    }

normalFinished:
    if (m_excelRW != NULL) {
        delete m_excelRW;
        m_excelRW = NULL;
    }

    this->quit();

    return;
}
