//xlang Source, Name:DockPanelManager.x 
//Date: Mon Feb 19:22:26 2021 
package Qtitan{
    public class DockPanelManager : Qt.QObject{
        public DockPanelManager(){
        
        }
        
        public DockPanelManager(long handle){
            super(handle);
        }

        public bool create(@NotNilptr Qt.QWidget parent) {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockPanelManager, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }   
        
        public bool create(@NotNilptr Qt.QMainWindow parent) {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtmDockPanelManager, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }  


        public Qt.QWidget managedWidget(){
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNQPM_MANAGEDWIDGET);
        }
        
        public DockLayoutPanel layoutPanel() {
            return (DockLayoutPanel)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNQPM_LAYOUTPANEL);
        }
        
        public DockLayoutPanel centralLayoutPanel() {
            return (DockLayoutPanel)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNQPM_CENTRALLAYOUTPANEL);
        }
        
        public DockWindow addDockWindow(DockPanelBase panel, Qt.QRect rect){
            return (DockWindow)Qt.QtXnl.long_int4(nativehandle, Qt.Constant.QTNQPM_ADDDOCKWINDOW, panel.nativehandle, rect.left, rect.top, rect.width(), rect.height());
        }
        
        public DockDocumentPanel addDocumentPanel(String title){
            return (DockDocumentPanel)Qt.QtXnl.object_get_handle_string(nativehandle, Qt.Constant.QTNQPM_ADDDOCUMENTPANEL, 0, title);
        }
        
        public void insertDocumentPanel(DockDocumentPanel documentPanel){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNQPM_INSERTDOCUMENTPANEL, documentPanel.nativehandle, 0);
        }
        
        public DockWidgetPanel addDockPanel(String title, DockPanelArea area, DockPanelBase targetPanel){
            return (DockWidgetPanel)Qt.QtXnl.object_get_string_handle_string_int(nativehandle,  Qt.Constant.QTNQPM_ADDDOCKPANEL, title,targetPanel != nilptr ? targetPanel.nativehandle : 0l, nilptr, area);
        }
        
        public DockWidgetPanel addDockPanel(String title, Qt.QSize sizeHint, DockPanelArea area, DockPanelBase targetPanel){
            return (DockWidgetPanel)Qt.QtXnl.object_get_string_handle_string_int(nativehandle,  Qt.Constant.QTNQPM_ADDDOCKPANELS, title, targetPanel != nilptr ? targetPanel.nativehandle : 0l, String.format("%d,%d",sizeHint.cx, sizeHint.cy), area);
        }
        
        public void insertDockPanel(DockWidgetPanel panel, DockPanelArea area, DockPanelBase targetPanel ){
            Qt.QtXnl.object_set_long_int_long(nativehandle,  Qt.Constant.QTNDPM_INSERTDOCKPANEL, panel.nativehandle, area, targetPanel != nilptr ? targetPanel.nativehandle : 0l);
        }
        
        public void removeDockPanel(DockWidgetPanel panel){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNQPM_REMOVEDOCKPANEL, panel.nativehandle);
        }
        
        public void clearDockPanels(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNQPM_CLEARDOCKPANELS);
        }

        public bool isDockPanelFloat(DockWidgetPanel panel){
            return 0 != Qt.QtXnl.core_getintlong(nativehandle, Qt.Constant.QTNQPM_ISDOCKPANELFLOAT, panel.nativehandle);
        }
        
        public void setDockPanelFloat(DockPanelBase panel, bool set){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNQPM_SETDOCKPANELFLOAT, panel.nativehandle, set ? 1 : 0);
        }

        public bool isDockPanelAutoHide(DockWidgetPanel panel) {
            return 0 != Qt.QtXnl.core_getintlong(nativehandle, Qt.Constant.QTNQPM_ISDOCKPANELAUTOHIDE, panel.nativehandle);
        }
        
        public void setDockPanelAutoHide(DockPanelBase panel, bool set){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNQPM_SETDOCKPANELAUTOHIDE, panel.nativehandle, set ? 1 : 0);
        }

        public void showDockPanel(DockWidgetPanel panel, bool setFocus){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNQPM_SHOWDOCKPANEL, panel.nativehandle, setFocus ? 1 : 0);
        }

        public bool isDockPanelClosed(DockWidgetPanel panel) {
            return 0 != Qt.QtXnl.core_getintlong(nativehandle, Qt.Constant.QTNQPM_ISDOCKPANELCLOSED, panel.nativehandle);
        }
        
        public void closeDockPanel(DockWidgetPanel panel){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNQPM_CLOSEDOCKPANEL, panel.nativehandle);
        }

        public int margin() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNQPM_MARGIN);
        }
        
        public void setMargin(int margin){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNQPM_SETMARGIN, margin);
        }

        public DockWidgetPanel activeDockPanel(){
           return (DockWidgetPanel)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNQPM_ACTIVEDOCKPANEL); 
        }

        public Qt.QWidget centralWidget() {
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNQPM_CENTRALWIDGET);
        }
        
        public void setCentralWidget(Qt.QWidget widget){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNQPM_SETCENTRALWIDGET, widget.nativehandle);
        }

        public String dockWindowTitle() {
            return (String)Qt.QtXnl.core_getString(nativehandle, Qt.Constant.QTNQPM_DOCKWINDOWTITLE);
        }
        
        public void setDockWindowTitle(String title){
            Qt.QtXnl.widget_slot_string(nativehandle, Qt.Constant.QTNQPM_SETDOCKWINDOWTITLE, title);
        }

        public bool isDockPanelFullContentsWhileDraggingShown() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNQPM_ISDOCKPANELFULLCONTENTSWHILEDRAGGINGSHOWN);
        }
        
        public void setDockPanelFullContentsWhileDraggingShown(bool show){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNQPM_SETDOCKPANELFULLCONTENTSWHILEDRAGGINGSHOWN, show);
        }

        public bool isDockPanelTransparentWhileDragging() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNQPM_ISDOCKPANELTRANSPARENTWHILEDRAGGING);
        }
        
        public void setDockPanelTransparentWhileDragging(bool transparent){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNQPM_SETDOCKPANELTRANSPARENTWHILEDRAGGING, transparent);
        }

        public bool isArrowMarkersShown() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNQPM_ISARROWMARKERSSHOWN);
        }
        
        public void setArrowMarkersShown(bool show){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNQPM_SETARROWMARKERSSHOWN, show);
        }

        public int defaultPaneFeatures(){
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNQPM_DEFAULTPANEFEATURES);
        }
        
        public void setDefaultPaneFeatures(int features){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNQPM_SETDEFAULTPANEFEATURES, features);
        }

        public void bestFit(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNQPM_BESTFIT);
        }

        public void beginUpdate(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNQPM_BEGINUPDATE);
        }
        
        public void endUpdate(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNQPM_ENDUPDATE);
        }
        
        public byte [] saveState(){
            return (byte[])Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.DPMSAVESTATE);
        }
        
        public void loadState(byte [] data){
            Qt.QtXnl.widget_set_object_value(nativehandle, Qt.Constant.DPMLOADSTATE, data);
        }
    };
};