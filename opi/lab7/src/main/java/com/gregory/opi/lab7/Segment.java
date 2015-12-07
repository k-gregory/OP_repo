package com.gregory.opi.lab7;

/**
 * Abstract segment
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
