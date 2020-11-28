//xlang Source, Name:qt5/QTabWidget.x
//Date: Thu Oct 16:38:58 2020 

package Qt{
    public class QTabWidget : QWidget{

        public QTabWidget(){
        
        }
        
        public QTabWidget(long handle){
            super(handle);
        }
        
        public bool create()override {
            nativehandle = QtXnl.createQObject(QType.qtTabWidget, this, 0);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public bool create(@NotNilptr QWidget parent)override {
            nativehandle = QtXnl.createQObject(QType.qtTabWidget, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }    

        public void currentChanged(int index){

        }

        public void tabCloseRequested(int index){

        }

        public void tabBarClicked(int index){

        }

        public void tabBarDoubleClicked(int index){

        }


        int addTab(QWidget widget, String text){
            return QtXnl.long_longstring(nativehandle, Constant.TABWIDGETADDTAB, widget.nativehandle, text);
        }
        
        int addTab(QWidget widget, QIcon icon, String label){
            return QtXnl.native_long2_string(nativehandle, Constant.TABWIDGETADDTAB, widget.nativehandle, icon.nativehandle, 0, label);
        }

        int insertTab(int index, QWidget widget, String label){
            return QtXnl.native_long2_string(nativehandle, Constant.TABWIDGETINSERTTAB, index, widget.nativehandle, 0, label);
        }
        
        int insertTab(int index, QWidget widget, QIcon icon, String label){
            return QtXnl.native_long2_string(nativehandle, Constant.TABWIDGETINSERTTAB2, index, widget.nativehandle, icon.nativehandle, label);
        }

        void removeTab(int index){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABWIDGETREMOVETAB, index);
        }

        bool isTabEnabled(int index) {
            return QtXnl.widget_get_int_bool(nativehandle, Constant.TABWIDGETISTABENABLED, index);
        }
        void setTabEnabled(int index, bool b){
            QtXnl.widget_set_int_bool_value(nativehandle, Constant.TABWIDGETSETTABENABLED, index, b);
        }

        String tabText(int index) {
            return (String)QtXnl.core_getStringlongint(nativehandle, Constant.TABWIDGETTABTEXT, 0, index);
        }
        void setTabText(int index, String text){
            QtXnl.widget_set_intstring_value(nativehandle, Constant.TABWIDGETSETTABTEXT, index, text);
        }
        
        void setTabIcon(int index, QIcon icon){
            QtXnl.object_set_long_int_long(nativehandle, Constant.TABWIDGETSETTABICON, 0, index, icon.nativehandle);
        }


        void setTabToolTip(int index, String  tip){
            QtXnl.widget_set_intstring_value(nativehandle, Constant.TABWIDGETSETTABTOOLTIP, index, tip);
        }
        String tabToolTip(int index) {
            return (String)QtXnl.core_getStringlongint(nativehandle, Constant.TABWIDGETTABTOOLTIP, 0, index);
        }

        void setTabWhatsThis(int index, String text){
            QtXnl.widget_set_intstring_value(nativehandle,Constant. TABWIDGETSETTABWHATSTHIS, index, text);
        }
        String tabWhatsThis(int index) {
            return (String)QtXnl.core_getStringlongint(nativehandle, Constant.TABWIDGETTABWHATSTHIS, 0, index);
        }


        int currentIndex() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.TABWIDGETCURRENTINDEX);
        }
        
        QWidget currentWidget() {
            return (QWidget)QtXnl.widget_get_object(nativehandle,Constant. TABWIDGETCURRENTWIDGET);
        }
        
        QWidget widget(int index) {
            return (QWidget)QtXnl.object_get_handle(nativehandle, Constant.TABWIDGETWIDGET, index);
        }
        
        int indexOf(QWidget widget) {
            return QtXnl.int_long_int_long_int_int(nativehandle, Constant.TABWIDGETINDEXOF, widget.nativehandle, 0, 0);
        }
        
        int count() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.TABWIDGETCOUNT);
        }

        enum TabPosition { North, South, West, East };


        TabPosition tabPosition() {
            return (TabPosition)QtXnl.widget_get_int_value(nativehandle, Constant.TABWIDGETTABPOSITION);
        }
        
        void setTabPosition(TabPosition tp){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABWIDGETSETTABPOSITION, tp);
        }

        bool tabsClosable() {   
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABWIDGETTABSCLOSABLE);
        }
        
        void setTabsClosable(bool closeable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABWIDGETSETTABSCLOSABLE, closeable);
        }

        bool isMovable(){
            return QtXnl.widget_get_bool_value(nativehandle, Constant.TABWIDGETISMOVABLE);
        }
        
        void setMovable(bool movable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABWIDGETSETMOVABLE, movable);
        }

        enum TabShape { Rounded, Triangular };


        TabShape tabShape() {
            return (TabShape)QtXnl.widget_get_int_value(nativehandle, Constant.TABWIDGETTABSHAPE);
        }
        
        void setTabShape(TabShape s){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABWIDGETSETTABSHAPE, s);
        }

        QSize sizeHint() {
            long lsize = QtXnl.long_get(nativehandle, Constant.TABWIDGETSIZEHINT);
            return new QSize(lsize >> 32 & 0xffffffff, lsize  & 0xffffffff);
        }
        
        QSize minimumSizeHint() {
            long lsize = QtXnl.long_get(nativehandle, Constant.TABWIDGETMINIMUMSIZEHINT);
            return new QSize(lsize >> 32 & 0xffffffff, lsize  & 0xffffffff);
        }
        
        int heightForWidth(int width) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.TABWIDGETHEIGHTFORWIDTH, width, 0);
        }
        
        bool hasHeightForWidth() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.TABWIDGETHASHEIGHTFORWIDTH);
        }

        void setCornerWidget(QWidget  w, Corner corner){
            QtXnl.object_get_long_int(nativehandle, Constant.TABWIDGETSETCORNERWIDGET, w.nativehandle, corner);
        }
        
        QWidget cornerWidget(Corner corner ) {
            return (QWidget)QtXnl.object_get_handle(nativehandle, Constant.TABWIDGETCORNERWIDGET, corner);
        }

        TextElideMode elideMode() {
            return (TextElideMode)QtXnl.widget_get_int_value(nativehandle, Constant.TABWIDGETELIDEMODE);
        }
        
        void setElideMode(TextElideMode tem){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABWIDGETSETELIDEMODE, tem);
        }

        QSize iconSize() {
            long lsize = QtXnl.long_get(nativehandle, Constant.TABWIDGETICONSIZE);
            return new QSize(lsize >> 32 & 0xffffffff, lsize  & 0xffffffff);
        }
        
        void setIconSize(QSize size){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.TABWIDGETSETICONSIZE, size.cx, size.cy);
        }

        bool usesScrollButtons() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.TABWIDGETUSESSCROLLBUTTONS);
        }
        
        void setUsesScrollButtons(bool useButtons){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABWIDGETSETUSESSCROLLBUTTONS, useButtons);
        }

        bool documentMode() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.TABWIDGETDOCUMENTMODE);
        }
        
        void setDocumentMode(bool set){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABWIDGETSETDOCUMENTMODE, set);
        }

        bool tabBarAutoHide() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.TABWIDGETAUTOHIDE);
        }
        
        void setTabBarAutoHide(bool enabled){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABWIDGETSETTABBARAUTOHIDE, enabled);
        }

        void clear(){
            QtXnl.widget_slot(nativehandle, Constant.TABWIDGETCLEAR);
        }

        QTabBar tabBar() {
            return (QTabBar)QtXnl.widget_get_object(nativehandle, Constant.TABWIDGETTABBAR);
        }


        void setCurrentIndex(int index){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABWIDGETSETCURRENTINDEX, index);
        }
        
        void setCurrentWidget(QWidget widget){
            QtXnl.widget_set_native_value(nativehandle, Constant.TABWIDGETSETCURRENTWIDGET, widget.nativehandle);
        }
    };
};