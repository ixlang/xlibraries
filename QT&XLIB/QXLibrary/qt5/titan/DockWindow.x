//xlang Source, Name:DockWindow.x 
//Date: Mon Feb 19:30:58 2021 
package Qtitan{
    public class DockWindow : DockWindowBase{
        public DockWindow(long handle){
            super(handle);
        }

        public bool create(@NotNilptr DockPanelManager parent) {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockWindow, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }   
        
        public void initializationWindow(DockPanelBase panelBase){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNDW_INITIALIZATIONWINDOW, panelBase.nativehandle, 0);
        }
        
        public void finalizationWindow(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDW_FINALIZATIONWINDOW);
        }
        
        public DockPanelManager dockManager() {
            return (DockPanelManager)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDW_DOCKMANAGER); 
        }
        
        public DockLayoutPanel layoutPanel() {
            return (DockLayoutPanel)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDW_LAYOUTPANEL); 
        }
    };
};