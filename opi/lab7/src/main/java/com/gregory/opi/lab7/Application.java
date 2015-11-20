package com.gregory.opi.lab7;

public class Application{
  public static void main(String[] args){
    Segment s  = new Segment(new Point2D(1,2),new Point2D(2,1));
    System.out.println(s);
    System.out.println(s.getLength());
    System.out.println(s.getAngle());
  }
}
