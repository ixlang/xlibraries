//xlang Source, Name:QCalendarWidget.x 
//Date: Mon Jan 19:00:48 2021 
package Qt{
    public class QCalendarWidget : QWidget{
        public QCalendarWidget(){
        }
        
        public QCalendarWidget(long handle){
            super(handle);
        }
        
        public bool create()override {
            nativehandle = QtXnl.createQObject(QType.qtCalendarWidget, this, 0);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public bool create(@NotNilptr QWidget parent)override {
            nativehandle = QtXnl.createQObject(QType.qtCalendarWidget, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }

        //signal
        public void setSelectedDate(QDate date){
            QtXnl.widget_set_v3int_value(nativehandle, Constant.QCW_SETSELECTEDDATE, date.year, date.mon, date.day);
        }
        
        public void setDateRange(QDate min, QDate max){
            QtXnl.widget_set_v3int_value(nativehandle, Constant.QCW_SETDATERANGE, (min.year << 16) | max.year, (min.mon << 16) | max.mon, (min.day << 16) | max.day);
        }
        
        public void setCurrentPage(int year, int month){
            QtXnl.widget_set_v3int_value(nativehandle, Constant.QCW_SETCURRENTPAGE, year, month, 0);
        }
        
        public void setGridVisible(bool show){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QCW_SETGRIDVISIBLE, show);
        }
        
        public void setNavigationBarVisible(bool visible){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QCW_SETNAVIGATIONBARVISIBLE, visible);
        }
        
        public void showNextMonth(){
            QtXnl.widget_slot(nativehandle, Constant.QCW_SHOWNEXTMONTH);
        }
        
        public void showPreviousMonth(){
            QtXnl.widget_slot(nativehandle, Constant.QCW_SHOWPREVIOUSMONTH);
        }
        
        public void showNextYear(){
            QtXnl.widget_slot(nativehandle, Constant.QCW_SHOWNEXTYEAR);
        }
        
        public void showPreviousYear(){
            QtXnl.widget_slot(nativehandle, Constant.QCW_SHOWPREVIOUSYEAR);
        }
        
        public void showSelectedDate(){
            QtXnl.widget_slot(nativehandle, Constant.QCW_SHOWSELECTEDDATE);
        }
        
        public void showToday(){
            QtXnl.widget_slot(nativehandle, Constant.QCW_SHOWTODAY);
        }

        // solt
        public void onSelectionChanged()override{
            
        }
        
        public void onClicked(int y, int m, int d){
            
        }
        
        public void onActivated(int y, int m, int d){
            
        }
        
        public void onCurrentPageChanged( int y, int m){
            
        }
    };
};