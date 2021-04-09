//xlang Source, Name:qt5/titan/DockLayoutPanel.x 
//Date: Tue Feb 12:04:48 2021 
package Qtitan{
    public class DockLayoutPanel : DockPanelBase{
        public DockLayoutPanel(long handle){
            super(handle);
        }
        
        public LayoutType layoutType() {
            return (LayoutType)Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNDLP_LAYOUTTYPE);
        }
        
        public bool isEmpty() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDLP_ISEMPTY);
        }
        
        public int childCount() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNDLP_CHILDCOUNT);
        }
    };
};