package com.gregory.opi.lab7;

public class Segment{
  private Point2D p1,p2;

  public Point2D getP2(){
    return this.p2;
  }
  public Point2D getP1(){
    return this.p1;
  }
  public void setP1(Point2D val){
    this.p1 = val;
  }
  public void setP2(Point2D val){
    this.p2 = val;
  }

  protected double dx(){
    return p1.getX()-p2.getX();
  }

  protected double dy(){
    return p1.getY()-p2.getY();
  }
 
  public double getLength(){
    double lx = dx();
    lx = lx*lx;
    double ly = dy();
    ly = ly*ly;

    return Math.sqrt(lx+ly);
  }

  public double getAngle(){
    return Math.atan(dy()/dx());
  }


  Segment(){
    setP1(new Point2D());
    setP2(new Point2D());
  }
  Segment(Point2D p1, Point2D p2){
    setP1(p1);
    setP2(p2);
  }
}
