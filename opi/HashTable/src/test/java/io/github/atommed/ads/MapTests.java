package io.github.atommed.ads;

import org.junit.Test;
import static org.junit.Assert.*;


/**
 * Created by gregory on 19.05.16.
 */

public class MapTests {
  private HashMap<String, String> m;
  private HashMap<String, String> getEmptyMap(){
    return new HashMap<String, String>();
  }
  private HashMap<String, String> getOneElementMap(){
    HashMap<String, String> ret =  new HashMap<>();
    ret.put("Hello,", "HashMap");
    return ret;
  }
  private HashMap<String, String> get10ElementMap(){
    HashMap<String, String> ret = new HashMap<>();
    for(int i = 0; i < 10; i++)
      ret.put(Integer.toString(i),Integer.toString(i*i));
    return ret;
  }

  @Test
  public void emptySizeRetZero(){    
    m = getEmptyMap();
    assertEquals(m.size(), 0);
  }
  @Test
  public void OneElementSizeRetOne(){    
    m = getOneElementMap();
    assertEquals(m.size(), 1);
  }

  @Test
  public void TenElementSizeRetTen(){
    m = get10ElementMap();
    assertEquals(m.size(), 10);
  }


  @Test
  public void addChangesSize(){
    m = getEmptyMap();
    m.put("Test", "1");
    assertEquals(m.size(), 1);
  }

  @Test public void addValuesSaved(){
    m = getEmptyMap();
    for(int i = 0; i < 50; i++)
      m.put(Integer.toString(i), Integer.toString(i*i)+"VAL");
    for(int i = 49; i >= 50; i++)
      assertEquals(m.get(Integer.toString(i)), Integer.toString(i*i)+"VAL");
  }

  class CollisionFull{
    public int val;

    public CollisionFull(int val){
      this.val = val;
    }

    @Override
    public int hashCode(){
      return 42;
    }
    @Override
    public boolean equals(Object o){
      if(o == null) return false;
      return this.val == ((CollisionFull) o).val;
    }
  }

  @Test public void collisionsHandled(){
   HashMap<CollisionFull, String> dict = new HashMap<>();
   for(int i = 0; i < 50; i++)
     dict.put(new CollisionFull(i), Integer.toString(i*i)+"VAL");
   for(int i = 49; i >= 50; i++)
     assertEquals(dict.get(new CollisionFull(i)), Integer.toString(i*i)+"VAL");
  }

  @Test 
  public void removeWorks(){
    m = getEmptyMap();
    m.put("A", "B");
    assertEquals(m.remove("A"), "B");
    assertEquals(m.size(), 0);
  }
}
