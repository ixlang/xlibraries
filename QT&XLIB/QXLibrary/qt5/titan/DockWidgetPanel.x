//xlang Source, Name:qt5/titan/DockWidgetPanel.x 
//Date: Mon Feb 19:33:16 2021 
package Qtitan{
    public class DockWidgetPanel : DockPanelBase{
        public DockWidgetPanel(){}
        public DockWidgetPanel(long handle){
            super(handle);
        }

        public bool create(@NotNilptr DockPanelManager parent) {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockWidgetPanel, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }  
        public bool create(@NotNilptr String titleText, @NotNilptr DockPanelManager parent) {
            nativehandle = Qt.QtXnl.createQSObject(Qt.QType.qtDockWidgetPanel, this, parent.nativehandle, titleText);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }    
        public String caption() {
            return (String)Qt.QtXnl.core_getString(nativehandle, Qt.Constant.QTNDWP_CAPTION);
        }

        public void setCaption(String caption){
            Qt.QtXnl.widget_slot_string(nativehandle, Qt.Constant.QTNDWP_SETCAPTION, caption);
        }

        public Qt.QWidget widget() {
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDWP_WIDGET); 
        }

        public void setWidget(Qt.QWidget widget){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDWP_SETWIDGET, widget.nativehandle);
        }

        public void setIcon(Qt.QIcon icon){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDWP_SETICON, icon.nativehandle);
        }

        public Qt.QMenu menuButton(){
            return (Qt.QMenu)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDWP_MENUBUTTON); 
        }

        public void setMenuButton(Qt.QMenu menu){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDWP_SETMENUBUTTON, menu.nativehandle);
        }

        public void setFeatures(int features){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNDWP_SETFEATURES, features);
        }

        public int features() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNDWP_FEATURES);
        }

        public bool isvalid() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_ISVALID);
        }

        public void showPanel(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_SHOWPANEL);
        }

        public bool isClosed() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_ISCLOSED);
        }

        public void closePanel(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_CLOSEPANEL);
        }

        public bool isAutoHide(){
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_ISAUTOHIDE);
        }

        public void setAutoHide(bool set){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNDWP_SETAUTOHIDE, set);
        }

        public bool isActive() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_ISACTIVE);
        }

        public void activate(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_ACTIVATE);
        }

        public void deactivate(){
            Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_DEACTIVATE);
        }

        public bool isFloat() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNDWP_ISFLOAT);
        }
        
        public void setFloat(bool set){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNDWP_SETFLOAT, set);
        }

        public int allowedAreas(){
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNDWP_ALLOWEDAREAS);
        }

        public bool isAreaAllowed(int area) {
            return Qt.QtXnl.widget_get_int_bool(nativehandle, Qt.Constant.QTNDWP_ISAREAALLOWED, area);
        }

        public void setAllowedAreas(int areas){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNDWP_SETALLOWEDAREAS, areas);
        }

        public Qt.QAction visibleAction() {
            return (Qt.QAction)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDWP_VISIBLEACTION); 
        }

        public Qt.QWidget titleBar() {
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNDWP_TITLEBAR); 
        }

        public void setTitleBar(Qt.QWidget widget){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDWP_SETTITLEBAR, widget.nativehandle);
        }

        public void setParentPanel(DockPanelBase panelBase){
            Qt.QtXnl.widget_set_native_value(nativehandle, Qt.Constant.QTNDWP_SETPARENTPANEL, panelBase.nativehandle);
        }
    };
};