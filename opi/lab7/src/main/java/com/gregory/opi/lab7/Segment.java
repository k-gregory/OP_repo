package com.gregory.opi.lab7;

/**
 * Created by gregory on 08.12.15.
 */
public interface Segment {
    /**
     * Calculate length of the segment
     */
    double getLength();
    /**
     * Returns angle between OX and the segment
     * @return angle in radians (-PI/2..PI/2)
     */
    double getAngle();
}
