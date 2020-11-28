//xlang Source, Name:qt5/QXSlider.x 
//Date: Thu Oct 16:38:58 2020 
package Qt{

    public class QTabBar : QAbstractSlider{

        public QTabBar(){
        
        }
        
        public QTabBar(long handle){
            super(handle);
        }
        
        public bool create()override {
            nativehandle = QtXnl.createQObject(QType.qtTabBar, this, 0);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public bool create(@NotNilptr QWidget parent)override {
            nativehandle = QtXnl.createQObject(QType.qtTabBar, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }    
        
        enum Shape { RoundedNorth, RoundedSouth, RoundedWest, RoundedEast,
                     TriangularNorth, TriangularSouth, TriangularWest, TriangularEast
        };


        enum ButtonPosition {
            LeftSide,
            RightSide
        };

        enum SelectionBehavior {
            SelectLeftTab,
            SelectRightTab,
            SelectPreviousTab
        };

        // callback
        public void currentChanged(int index){

        }

        public void tabCloseRequested(int index){

        }

        public void tabMoved(int from, int to){
            
        }
        
        public void tabBarClicked(int index){

        }

        public void tabBarDoubleClicked(int index){

        }
        
        // methods
        public Shape shape() {
            return (Shape)QtXnl.widget_get_int_value(nativehandle, Constant.TABBARSHAPE);
        }
        
        public void setShape(Shape shape){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABBARSETSHAPE, shape);
        }

        public int addTab( String text){
            return QtXnl.widget_set_intstring_value(nativehandle, Constant.TABBARADDTAB, 0, text);
        }
        public int addTab( QIcon icon,  String text){
            return QtXnl.long_longstring(nativehandle, Constant.TABBARADDTAB, icon.nativehandle, text);
        }

        public int insertTab(int index,  String text){
            return QtXnl.widget_set_intstring_value(nativehandle, Constant.TABBARINSERTTAB, index, text);
        }

        public void removeTab(int index){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABBARREMOVETAB, index);
        }
        public void moveTab(int from, int to){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.TABBARMOVETAB, from, to);
        }

        public bool isTabEnabled(int index) {
            return QtXnl.widget_get_int_bool(nativehandle, Constant.TABBARISTABENABLED, index);
        }
        
        public void setTabEnabled(int index, bool b){
            QtXnl.widget_set_int_bool_value(nativehandle, Constant.TABBARSETTABENABLED, index, b);
        }

        public String tabText(int index) {
            return (String)QtXnl.core_getStringlongint(nativehandle, Constant.TABBARTABTEXT, 0, index);
        }
        
        public void setTabText(int index,  String text){
            QtXnl.widget_set_intstring_value(nativehandle, Constant.TABBARSETTABTEXT, index, text);
        }

        long tabTextColor(int index) {
            return QtXnl.long_intlong(nativehandle, Constant.TABBARTABTEXTCOLOR, index);
        }
        
        public void setTabTextColor(int index,  long color){
            QtXnl.void_long2(nativehandle, Constant.TABBARSETTABTEXTCOLOR, index, color);
        }
        
        public void setTabIcon(int index,  QIcon icon){
            QtXnl.object_set_long_int_long(nativehandle, Constant.TABBARSETTABICON, 0, index, icon.nativehandle);
        }

        public TextElideMode elideMode() {
            return (TextElideMode)QtXnl.widget_get_int_value(nativehandle, Constant.TABBARELIDEMODE);
        }
        
        public void setElideMode(TextElideMode tem){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABBARSETELIDEMODE, tem);
        }


        public void setTabToolTip(int index,  String tip){
            QtXnl.widget_set_intstring_value(nativehandle, Constant.TABBARSETTABTOOLTIP, index, tip);
        }
        
        public String tabToolTip(int index) {
            return (String)QtXnl.core_getStringlongint(nativehandle, Constant.TABBARTABTOOLTIP, 0, index);
        }

        public void setTabWhatsThis(int index,  String text){
            QtXnl.widget_set_intstring_value(nativehandle, Constant.TABBARSETTABWHATSTHIS, index, text);
        }
        
        public String tabWhatsThis(int index) {
            return (String)QtXnl.core_getStringlongint(nativehandle, Constant.TABBARTABWHATSTHIS, 0, index);
        }


        /*public void setTabData(int index,  QVariant data){
            
        }
        
        public QVariant tabData(int index) {
            
        }

        public QRect tabRect(int index) {
            
        }*/
        
        public int tabAt( QPoint pos) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.TABBARTABAT, pos.x, pos.y);
        }

        public int currentIndex() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.TABBARCURRENTINDEX);
        }
        
        public int count() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.TABBARCOUNT);
        }

        public QSize sizeHint(){
            long lsize = QtXnl.long_get(nativehandle, Constant.TABBARSIZEHINT);
            return new QSize(lsize >> 32 & 0xffffffff, lsize  & 0xffffffff);
        }
        
        public QSize minimumSizeHint(){
            long lsize = QtXnl.long_get(nativehandle, Constant.TABBARMINIMUMSIZEHINT);
            return new QSize(lsize >> 32 & 0xffffffff, lsize  & 0xffffffff);
        }

        public void setDrawBase(bool drawTheBase){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARSETDRAWBASE, drawTheBase);
        }
        
        public bool drawBase(){
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBARDRAWBASE);
        }

        public QSize iconSize(){
            long lsize = QtXnl.long_get(nativehandle, Constant.TABBARICONSIZE);
            return new  QSize(lsize >> 32 & 0xffffffff, lsize  & 0xffffffff);
        }
        
        public void setIconSize( QSize size){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.TABBARSETICONSIZE, size.cx, size.cy);
        }

        public bool usesScrollButtons() {
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBARUSESSCROLLBUTTONS);
        }
        
        public void setUsesScrollButtons(bool useButtons){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARUSEBUTTONS, useButtons);
        }

        public bool tabsClosable() {
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBARTABSCLOSABLE);
        }
        
        public void setTabsClosable(bool closable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARSETTABSCLOSABLE, closable);
        }

        public void setTabButton(int index, ButtonPosition position, QWidget widget){
            QtXnl.object_set_long_int_long(nativehandle, Constant.TABBARSETTABBUTTON, index, position, widget.nativehandle);
        }
        
        public QWidget tabButton(int index, ButtonPosition position) {
            return (QWidget)QtXnl.object_get_handle2(nativehandle, Constant.TABBARTABBUTTON, index, position);
        }

        public SelectionBehavior selectionBehaviorOnRemove() {
            return (SelectionBehavior)QtXnl.widget_get_int_value(nativehandle, Constant.TABBARSELECTIONBEHAVIORONREMOVE);
        }
        
        public void setSelectionBehaviorOnRemove(SelectionBehavior behavior){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABBARSETSELECTIONBEHAVIORONREMOVE, behavior);
        }

        public bool expanding() {
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBAREXPANDING);
        }
        
        public void setExpanding(bool enabled){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARSETEXPANDING, enabled);
        }

        public bool isMovable() {
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBARISMOVABLE);
        }
        
        public void setMovable(bool movable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARSETMOVABLE, movable);
        }

        public bool documentMode() {
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBARDOCUMENTMODE);
        }
        
        public void setDocumentMode(bool set){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARSETDOCUMENTMODE, set);
        }

        public bool autoHide() {
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBARAUTOHIDE);
        }
        
        public void setAutoHide(bool hide){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARSETAUTOHIDE, hide);
        }

        public bool changeCurrentOnDrag() {
            return QtXnl.widget_get_bool_value(nativehandle,Constant.TABBARCHANGECURRENTONDRAG);
        }
        
        public void setChangeCurrentOnDrag(bool change){
            QtXnl.widget_set_bool_value(nativehandle, Constant.TABBARSETCHANGECURRENTONDRAG, change);
        }


        public String accessibleTabName(int index) {
            return (String)QtXnl.object_get_handle(nativehandle, Constant.TABBARACCESSIBLETABNAME, index);
        }
        
        public void setAccessibleTabName(int index,  String name){
            QtXnl.widget_set_intstring_value(nativehandle, Constant.TABBARSETACCESSIBLETABNAME, index, name);
        }

        public void setCurrentIndex(int index){
            QtXnl.widget_set_vint_value(nativehandle, Constant.TABBARSETCURRENTINDEX, index);
        }
    };
};