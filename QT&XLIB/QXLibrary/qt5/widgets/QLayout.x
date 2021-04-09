//xlang Source, Name:QLayout.x 
//Date: Wed May 02:09:01 2020 
package Qt{
    public class QLayout : QObject{
        public QLayout(){
      
        }
        public QLayout(long h){
            super(h);
        }
        
        public void setContentsMargins(int l,int t,int r, int b){
            long x = l << 32 | t, y = r << 32 |b;
            QtXnl.void_long2(nativehandle, Constant.QLAYOUT_SETCONTENTSMARGINS, x, y);
        }
                
        public void setMargin(int m){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QLAYOUT_SETMARGIN, m);
        }
    };
};