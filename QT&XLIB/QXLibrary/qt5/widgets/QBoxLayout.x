//xlang Source, Name:qt5/widgets/QBoxLayout.x 
//Date: Wed May 02:04:09 2020 
package Qt{
    public class QBoxLayout : QLayout{
        public QBoxLayout(){
        }
        public QBoxLayout(long h){
            super(h);
        }
        public void addWidget(@NotNilptr QWidget  w){
            QtXnl.widget_set_intlongint_value(nativehandle, Constant.LAYTOUADDWIDGET, w.nativehandle, 0, 0);
        }
        public void addStretch(int n){
            QtXnl.widget_set_vint_value(nativehandle, Constant.BOXADDSTRETCH, n);
        }
        public void addSpacing(int n){
            QtXnl.widget_set_vint_value(nativehandle, Constant.BOXADDSPACING, n);
        }
        public void setSpacing(int n){
            QtXnl.widget_set_vint_value(nativehandle, Constant.BOXSETSPACING, n);
        }
        public void setStretch(int id, int n){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.BOXSETSTRETCH, id, n);
        }
    };
};