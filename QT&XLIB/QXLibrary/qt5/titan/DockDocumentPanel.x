//xlang Source, Name:qt5/titan/DockDocumentPanel.x 
//Date: Mon Feb 19:33:49 2021 
package Qtitan{
    public class DockDocumentPanel : DockWidgetPanel{
        public DockDocumentPanel(){}
        public DockDocumentPanel(long handle){
            super(handle);
        }

        public bool create(@NotNilptr DockPanelManager parent) {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockDocumentPanel, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public void setParentPanel(DockPanelBase panelBase){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDDP_SETPARENTPANEL, panelBase.nativehandle);
        }
    };
};