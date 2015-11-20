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

    p1 = new Point2D(1,2);
    p2 = new Point2D(2,1);
    s = new Segment(p1,p2);
    assertEquals(s.getLength(),Math.sqrt(2));
  }
}
