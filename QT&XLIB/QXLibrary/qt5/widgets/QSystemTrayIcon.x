//xlang Source, Name:qt5/widgets/QSystemTrayIcon.x 
//Date: Wed Jan 15:45:14 2021 

package Qt{
    public class QSystemTrayIcon : QObject{
    
        private onSystemTrayListener _listener = nilptr;

        public QSystemTrayIcon() {//构造

        }

        public bool create() {
            nativehandle = QtXnl.createQObject(QType.qtSystemTrayIcon, this, 0);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public bool create(@NotNilptr QWidget parent) {
            nativehandle = QtXnl.createQObject(QType.qtSystemTrayIcon, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }  
        
        
        public onSystemTrayListener getOnSystemTrayListener(){
            return _listener;
        }
        
        public void setOnSystemTrayListener(onSystemTrayListener l){
            _listener = l;
        }
        
        public bool isVisible() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QSTI_VISIBLE);
        }
        
        public void setVisible(bool visible){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QSTI_SETVISIBLE, visible);
        }
        
        public void setIcon(QIcon icon){
            QtXnl.widget_set_native_value(nativehandle, Constant.QSTI_SETICON, icon.nativehandle);
        }
        
        public QIcon icon(){
            return new QIcon(QtXnl.long_get(nativehandle, Constant.QSTI_GETICON));
        }
        
        public void setContextMenu(QMenu menu){
            QtXnl.widget_set_native_value(nativehandle, Constant.QSTI_SETCONTEXTMENU, menu.nativehandle);
        }
        
        public QMenu contextMenu(){
            return (QMenu)QtXnl.widget_get_object(nativehandle, Constant.QSTI_GETCONTEXTMENU);
        }
        
        public String toolTip() {
            return (String)QtXnl.core_getString(nativehandle, Constant.QSTI_TOOLTIP);
        }
        
        public void setToolTip(String tip){
            QtXnl.widget_slot_string(nativehandle, Constant.QSTI_SETTOOLTIP, tip);
        }
    
        public void show() { setVisible(true); }
        public void hide() { setVisible(false); }
        
        public static bool isSystemTrayAvailable(){
            return QtXnl.widget_get_bool_value(0, Constant.QSTI_ISSYSTEMTRAYAVAILABLE);
        }
        
        public static bool supportsMessages(){
            return QtXnl.widget_get_bool_value(0, Constant.QSTI_SUPPORTSMESSAGES);
        }
    
        public void showMessage(String title, String msg, QIcon icon, int msecs /*= 10000*/){
            QtXnl.object_get_string_handle_string_int(nativehandle, Constant.QSTI_SHOWMESSAGE, title, icon != nilptr ? icon.nativehandle : 0l, msg, msecs);
        }
        
        public void showMessage(String title, String msg, MessageIcon icon /* = QSystemTrayIcon::Information */, int msecs/* = 10000*/){
            QtXnl.long_string2_int2(nativehandle, Constant.QSTI_SHOWMESSAGE,title, msg, icon.value(), msecs);
        }
        
        public void activated(int reason){
            if (_listener != nilptr){
                _listener.activated(this, (ActivationReason)reason);
            }
        }
        
        public void messageClicked(){
            if (_listener != nilptr){
                _listener.messageClicked(this);
            }
        }
    };
};