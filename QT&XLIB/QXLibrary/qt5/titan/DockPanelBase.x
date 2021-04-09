//xlang Source, Name:DockPanelBase.x 
//Date: Mon Feb 19:31:47 2021 
package Qtitan{
    public class DockPanelBase : Qt.QWidget{
        public DockPanelBase(){}
        public DockPanelBase(long handle){
            super(handle);
        }
        
        public DockPanelManager dockManager() {
            return (DockPanelManager)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDPB_DOCKMANAGER);
        }

        public DockPanelBase parentPanel(){
            return (DockPanelBase)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDPB_PARENTPANEL);
        }
        
        public void setParentPanel(DockPanelBase panelBase){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNDPB_SETPARENTPANEL, panelBase.nativehandle, 0);
        }

        public DockWindowBase topDockWindow() {
            return (DockWindowBase)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDPB_TOPDOCKWINDOW);
        }
        
        public DockWindowBase dockWindow() {
            return (DockWindowBase)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDPB_DOCKWINDOW);
        }
        
        public void setDockWindow(DockWindowBase dockWindow){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNDPB_SETDOCKWINDOW, dockWindow.nativehandle, 0);
        }
    };
};
