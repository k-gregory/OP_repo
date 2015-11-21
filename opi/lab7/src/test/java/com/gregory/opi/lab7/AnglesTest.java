package com.gregory.opi.lab7;

import static org.junit.Assert.assertEquals;
import org.junit.Test;

import com.gregory.opi.lab7.Point2D;
import com.gregory.opi.lab7.Segment;

public class AnglesTest{
  @Test
  public void usualAngles(){
    Point2D p1,p2;
    Segment s;

    s = new Segment(new Point2D(0,0),new Point2D(1,1));
    assertEquals(Math.PI/4,s.getAngle(), 0.05);

    s = new Segment(new Point2D(0,0),new Point2D(1,0));
    assertEquals(0,s.getAngle(), 0.05);
    
    s = new Segment(new Point2D(0,0),new Point2D(2,3));
    
    s = new Segment(new Point2D(0,0),new Point2D(1,1));
    assertEquals(Math.PI/4,s.getAngle(), 0.05);
  }
}
