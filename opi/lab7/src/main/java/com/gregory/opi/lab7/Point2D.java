package com.gregory.opi.lab7;

/**
 * Class representing a point on two-dimensional Cartesian coordinate system
 */
public class Point2D {
    /** Segment coordinate */
    private double x, y;

    public Point2D() {
        setX(0);
        setY(0);
    }

    public Point2D(double x, double y) {
        setX(x);
        setY(y);
    }

    public double getX() {
        return this.x;
    }

    public void setX(double val) {
        this.x = val;
    }

    public double getY() {
        return this.y;
    }

    public void setY(double val) {
        this.y = val;
    }

    @Override
    public String toString() {
        return "(" + getX() + "," + getY() + ")";
    }
}
