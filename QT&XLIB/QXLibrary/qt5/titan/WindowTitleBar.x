//xlang Source, Name:WindowTitleBar.x 
//Date: Mon Feb 19:16:51 2021 
package Qtitan{
    public class WindowTitleBar : Qt.QObject{
        public WindowTitleBar(){
        }
        public WindowTitleBar(long handle){
            super(handle);
        }
        public void setVisible(bool visible){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNWT_SETVISIBLE, visible);
        }
        public bool isVisible(){
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNWT_ISVISIBLE);
        }
        public void show(){
            Qt.QtXnl.widget_slot(nativehandle, Qt.Constant.QTNWT_SHOW);
        }
        public void hide(){
            Qt.QtXnl.widget_slot(nativehandle, Qt.Constant.QTNWT_HIDE);
        }
        public void update(){
            Qt.QtXnl.widget_slot(nativehandle, Qt.Constant.QTNWT_UPDATE);
        }
        public void setWidget(Qt.QWidget widget, WidgetAlign align){
            Qt.QtXnl.object_get_long_int(nativehandle, Qt.Constant.QTNWT_SETWIDGET, widget.nativehandle, align);
        }
        public Qt.QWidget widget() {
            return (Qt.QWidget)Qt.QtXnl.widget_get_object(nativehandle, Qt.Constant.QTNWT_WIDGET);
        }
        public bool styledFrame() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNWT_STYLEDFRAME);
        }
        public void setStyledFrame(bool styled){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNWT_SETSTYLEDFRAME, styled);
        }
        public bool blurBehindWindowEnabled() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNWT_BLURBEHINDWINDOWENABLED);
        }
        public void setBlurBehindWindowEnabled(bool enabled){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNWT_SETBLURBEHINDWINDOWENABLED, enabled);
        }
        public bool extendViewIntoTitleBar() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNWT_EXTENDVIEWINTOTITLEBAR);
        }
        public void setExtendViewIntoTitleBar(bool extend){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNWT_SETEXTENDVIEWINTOTITLEBAR, extend);
        }
        public void setTitleHeight(int height){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNWT_SETTITLEHEIGHT, height);
        }
        public int titleHeight() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNWT_TITLEHEIGHT);
        }
        public void setBorderThickness(int thickness){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNWT_SETBORDERTHICKNESS, thickness);
        }
        public int borderThickness() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNWT_BORDERTHICKNESS);
        }
        public bool isSysMenuButtonVisible() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNWT_ISSYSMENUBUTTONVISIBLE);
        }
        public void setSysMenuButtonVisible(bool visible){
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNWT_SETSYSMENUBUTTONVISIBLE, visible);
        }
        public SysButtonKind sysButtonKind() {
            return (SysButtonKind)Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNWT_SYSBUTTONKIND);
        }
        public void setSysButtonKind(SysButtonKind kind){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNWT_SETSYSBUTTONKIND, kind);
        }
        public int backgroundColor() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNWT_BACKGROUNDCOLOR);
        }
        public void setBackgroundColor(int color){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNWT_SETBACKGROUNDCOLOR, color);
        }
        public int frameColor() {
            return Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNWT_FRAMECOLOR);
        }
        public bool isQWizardSupports() {
            return Qt.QtXnl.widget_get_bool_value(nativehandle, Qt.Constant.QTNWT_ISQWIZARDSUPPORTS);
        }
        public void setQWizardSupports(bool supports) {
            Qt.QtXnl.widget_set_bool_value(nativehandle, Qt.Constant.QTNWT_SETQWIZARDSUPPORTS, supports);
        }
        public void removeAndDelete(){
            Qt.QtXnl.widget_slot(nativehandle, Qt.Constant.QTNWT_REMOVEANDDELETE);
        }
        public static WindowTitleBar get(Qt.QWidget w){
            return (WindowTitleBar)Qt.QtXnl.widget_get_object(w.nativehandle, Qt.Constant.QTNWTB_GET);
        }
        public static WindowTitleBar find(Qt.QWidget w){
            return (WindowTitleBar)Qt.QtXnl.widget_get_object(w.nativehandle, Qt.Constant.QTNWTB_FIND);
        }
        public void backRequested(){
        
        }
        public void showHelp(){
        
        }
  
    };
};