package com.gregory.opi.lab7;

/**
 * Class representing a segment on two-dimensional Cartesian coordinate system
 */
public class Segment2D implements Segment {

    /*Segment ending*/
    private Point2D p1, p2;

    public Segment2D() {
        setP1(new Point2D());
        setP2(new Point2D());
    }

    /**
     * Create segment with specified beginning and ending points
     *
     * @param p1 begin point
     * @param p2 end point
     */
    public Segment2D(Point2D p1, Point2D p2) {
        setP1(p1);
        setP2(p2);
    }

    public Point2D getP2() {
        return this.p2;
    }

    public void setP2(Point2D val) {
        this.p2 = val;
    }

    public Point2D getP1() {
        return this.p1;
    }

    public void setP1(Point2D val) {
        this.p1 = val;
    }

    /**
     * @return Difference between first point's X coordinate, and second point's X coordinate
     */
    protected double dx() {
        return p2.getX() - p1.getX();
    }

    /**
     * @return Difference between first point's Y coordinate, and second point's Y coordinate
     */
    protected double dy() {
        return p2.getY() - p1.getY();
    }

    public double getLength() {
        //Length = (dx^2+dy^2)^(1/2)
        double lx = dx();
        lx = lx * lx;//dx^2
        double ly = dy();
        ly = ly * ly;//dy^2

        return Math.sqrt(lx + ly);
    }

    public double getAngle() {
        return Math.atan2(dy(), dx());
    }

    @Override
    public String toString() {
        return "Segment2D from " + getP1() + " to " + getP2();
    }
}
