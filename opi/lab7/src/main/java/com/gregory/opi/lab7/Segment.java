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
  
  //Difference between first point's X coord, and second point's X coord
  protected double dx(){
    return p1.getX()-p2.getX();
  }

  //Difference between first point's Y coord, and second point's Y coord
  protected double dy(){
    return p1.getY()-p2.getY();
  }
 
  //Gets length of the segment
  public double getLength(){
    //Length = (dx^2+dy^2)^(1/2)
    double lx = dx();
    lx = lx*lx;//dx^2
    double ly = dy();
    ly = ly*ly;//dy^2

    return Math.sqrt(lx+ly);
  }

  //Gets between OX and the segment
  public double getAngle(){
    if(dx()==0){ //Vertical line
      if(dy()>0) //Angle == 90 or 270?
	return Math.PI/2;
      else return Math.PI*3/2;
    }
    return Math.atan(dy()/dx());
  }

  @Override
  public String toString(){
    return "Segment from "+getP1()+" to "+getP2();
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
