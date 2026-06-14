public class HanoiTowers {
  public static void main(String[] args) {
    moveDisk(2);
  }
  
  private static HelperArray move(int cnt) {
    if ( cnt < 1 ) return null;
    
    int total = 0;
    for ( int i = 1; i <= cnt; i++ ) {
      total = total * 2 + 1;
    }
    
    HelperArray temp = new HelperArray((total-1)/2);
    HelperArray result = new HelperArray(total);
 
    int n = 1;
    result.add("A->C");
    while ( n < cnt ) {
      temp.clear();
      for ( int i = 0; i < result.size(); i++ ) {
        temp.add(result.get(i));
      }
      
      result.clear();
      for (int i = 0; i < temp.size(); i++) {
        String elt = temp.get(i);
        String s = null;
        
        if (elt.equals("A->B")) s = "A->C";
        if (elt.equals("A->C")) s = "A->B";
        if (elt.equals("B->A")) s = "C->A";
        if (elt.equals("B->C")) s = "C->B";
        if (elt.equals("C->A")) s = "B->A";
        if (elt.equals("C->B")) s = "B->C";
        
        result.add(s);  
 
      }
 
      result.add("A->C");
      
      for (int i = 0; i < temp.size(); i++) {
        String elt = temp.get(i);
        String s = null;
          
        if (elt.equals("A->B")) s = "B->A";
        if (elt.equals("A->C")) s = "B->C";
        if (elt.equals("B->A")) s = "A->B";
        if (elt.equals("B->C")) s = "A->C";
        if (elt.equals("C->A")) s = "C->B";
        if (elt.equals("C->B")) s = "C->A";
                        
        result.add(s);
 
      }
        
      ++n;
    }
    return result;
  }
  
  public static void moveDisk(int cnt) {
    HelperArray ha = move(cnt);
    if ( ha != null ) {
      for (int i = 0; i < ha.size(); i++) {
        System.out.println(ha.get(i));
      }      
    }
  }
 
}
