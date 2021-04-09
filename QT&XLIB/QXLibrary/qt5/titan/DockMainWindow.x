//xlang Source, Name:DockMainWindow.x 
//Date: Mon Feb 19:03:12 2021 

package Qtitan{
    public class DockMainWindow : Qt.QWidget{
        public DockMainWindow(){
        
        }
        
        public DockMainWindow(long handle){
            super(handle);
        }
        
        public bool create()override {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockMainWindow, this, 0);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public bool create(@NotNilptr Qt.QWidget parent)override {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockMainWindow, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }   


        public WindowTitleBar titleBar(){
            return (WindowTitleBar)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNTITLEBAR);
        }
        
        public Qt.QWidget titleBarWidget(){
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNTITLEBARWIDGET);
        }
        
        public Qt.QMenuBar menuBar(){
            return (Qt.QMenuBar)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNMENUBAR);
        }
        
        public Qt.QStatusBar statusBar(){
            return (Qt.QStatusBar)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNSTATUSBAR);
        }
        
        public Qt.QWidget centralWidget(){
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNCENTRALWIDGET);
        }
        
        public DockBarManager dockBarManager(){
            return (DockBarManager)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDOCKBARMANAGER);
        }
                
        public DockPanelManager dockPanelManager(){
            return (DockPanelManager)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDOCKPANELMANAGER);
        }
        
        public DockToolBar addToolBar(String title, Qtitan.DockBarArea barPosition){
            return (DockToolBar)Qt.QtXnl.object_get_handle_string(nativehandle, Qt.Constant.QTNADDTOOLBAR, barPosition, title);
        }
        
        public bool insertDockBar(DockToolBar bar, Qtitan.DockBarArea position){
            return 0 != Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNINSERTDOCKBAR, bar.nativehandle, position);
        }
        
        public void insertDockBar(DockToolBar before, DockToolBar bar){
            Qt.QtXnl.void_long2(nativehandle, Qt.Constant.QTNINSERTDOCKBAR, before.nativehandle, bar.nativehandle);
        }
        
        public void removeDockBar(DockToolBar bar){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNREMOVEDOCKBAR, bar.nativehandle);
        }
        
        public void moveDockBar(DockToolBar before, DockToolBar bar){
            Qt.QtXnl.void_long2(nativehandle, Qt.Constant.QTNMOVEDOCKBAR, before.nativehandle, bar.nativehandle);
        }
        
        public void clearDockBars(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNCLEARDOCKBARS);
        }
        
        public DockWindow addDockWindow(DockPanelBase panel, Qt.QRect rect){
            return (DockWindow)Qt.QtXnl.long_int4(nativehandle, Qt.Constant.QTNADDDOCKWINDOW, panel.nativehandle, rect.left, rect.top, rect.width(), rect.height());
        }
        
        public DockDocumentPanel addDocumentPanel(String title ){
            return (DockDocumentPanel)Qt.QtXnl.object_get_handle_string(nativehandle, Qt.Constant.QTNADDDOCUMENTPANEL, 0, title);
        }
        
        public void insertDocumentPanel(DockDocumentPanel documentPanel){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNINSERTDOCUMENTPANEL, documentPanel.nativehandle, 0);
        }
        
        public DockWidgetPanel addDockPanel(String title, Qtitan.DockPanelArea area, DockPanelBase targetPanel){
            return (DockWidgetPanel)Qt.QtXnl.object_get_string_handle_string_int(nativehandle,  Qt.Constant.QTNADDDOCKPANEL, title, targetPanel != nilptr ? targetPanel.nativehandle : 0l, nilptr, area);
        }
        
        public DockWidgetPanel addDockPanel(String title, Qt.QSize sizeHint, Qtitan.DockPanelArea area, DockPanelBase targetPanel){
            return (DockWidgetPanel)Qt.QtXnl.object_get_string_handle_string_int(nativehandle,  Qt.Constant.QTNADDDOCKPANELS, title, targetPanel != nilptr ? targetPanel.nativehandle : 0l, String.format("%d,%d",sizeHint.cx, sizeHint.cy), area);
        }
        
        public void insertDockPanel(DockWidgetPanel panel, Qtitan.DockPanelArea area, DockPanelBase targetPanel){
            Qt.QtXnl.object_set_long_int_long(nativehandle,  Qt.Constant.QTNDMW_INSERTDOCKPANEL, panel.nativehandle, area, targetPanel != nilptr ? targetPanel.nativehandle : 0l);
        }
               
        public void removeDockPanel(DockWidgetPanel panel){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNREMOVEDOCKPANEL, panel.nativehandle);
        }
        
        public void clearDockPanels(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNCLEARDOCKPANELS);
        }
        
        public byte [] saveState(){
            return (byte[])Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.DMSAVESTATE);
        }
        
        public void loadState(byte [] data){
            Qt.QtXnl.widget_set_object_value(nativehandle, Qt.Constant.DMLOADSTATE, data);
        }
    };
};