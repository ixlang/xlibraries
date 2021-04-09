//xlang Source, Name:DockBarManager.x 
//Date: Mon Feb 19:20:22 2021 
package Qtitan{
    public class DockBarManager : Qt.QObject{
        public DockBarManager(){
            
        }
        
        public DockBarManager(long handle){
            super(handle);
        }

        public bool create(@NotNilptr Qt.QWidget parent) {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockBarManager, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }  
        
        public Qt.QWidget managedWidget() {
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDB_MANAGEDWIDGET);
        }
        
        public DockToolBar addToolBar(String name, DockBarArea position){
            return (DockToolBar)Qt.QtXnl.object_get_handle_string(nativehandle, Qt.Constant.QTNDB_ADDTOOLBAR, position, name);
        }
        
        public void insertDockBar(DockToolBar before, DockToolBar bar){
            Qt.QtXnl.void_long2(nativehandle, Qt.Constant.QTNDB_INSERTDOCKBAR, before.nativehandle, bar.nativehandle);
        }
        
        public bool insertDockBar(DockToolBar bar, DockBarArea position){
            return 0 != Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNDB_INSERTDOCKBAR, bar.nativehandle, position);
        }
        
        public void moveDockBar(DockToolBar before, DockToolBar bar){
            Qt.QtXnl.void_long2(nativehandle, Qt.Constant.QTNDB_MOVEDOCKBAR, before.nativehandle, bar.nativehandle);
        }
        
        public void removeDockBar(DockToolBar bar){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDB_REMOVEDOCKBAR, bar.nativehandle);
        }
        
        public void clearDockBars(){
            Qt.QtXnl.widget_slot(nativehandle, Qt.Constant.QTNDB_CLEARDOCKBARS);
        }

        public Qt.QWidget centralWidget() {
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDB_CENTRALWIDGET);
        }
        
        public void setCentralWidget(Qt.QWidget widget){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDB_SETCENTRALWIDGET, widget.nativehandle);
        }
        
        public int dockBarCount() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNDB_DOCKBARCOUNT);
        }
        
        public byte [] saveState(){
            return (byte[])Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.DBMSAVESTATE);
        }
        
        public void loadState(byte [] data){
            Qt.QtXnl.widget_set_object_value(nativehandle, Qt.Constant.DBMLOADSTATE, data);
        }
    };
};