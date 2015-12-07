package com.gregory.opi.lab7;

public class Point2D{
  private double x,y;
  public double getX(){
    return this.x;
  }
  public double getY(){
    return this.y;
  }

  public void setX(double val){
    this.x = val;
  }
  public void setY(double val){
    this.y = val;
  }

  
  public Point2D(){
    setX(0);
    setY(0);
  }
  public Point2D(double x, double y){
    setX(x);
    setY(y);
  }

  @Override
  public String toString(){
    return "("+getX()+","+getY()+")";
  } 
}
