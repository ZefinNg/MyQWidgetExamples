# MyQWidgetExamples
基于QWidget的示例



# Excel2Ts

已完成接口：

- [x] bool isOpen();
- [x] bool openFile(QString filePath);
- [x] QString getTitle();
- [ ] bool setTitle(QString title);//TODO:无法正常设置成功
- [x] QString getWorksheetName();
- [x] bool setWorksheetName(QString worksheetName);
- [x] int getWorksheetCount();
- [x] bool setCurrentWorkSheet(int index);
- [x] void appendWorksheet();
- [ ] void deleteCurrentWorksheet();//TODO:当工作表有数据时，无法删除
- [x] int getRows();
- [x] int getColumns();
- [x] int getStartRows();
- [x] int getStartColumns();
- [x] QString getCellText(int row, int col);
- [x] bool setCellText(QString text, int row, int col, ALIGNMENT_H alignmentH = ALIGN_LEFT, ALIGNMENT_V alignmentV = ALIGN_TOP, bool wrap = false);
- [x] void closeFile();