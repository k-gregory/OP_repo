package com.gregory.opi.lab7.test;

import static org.junit.Assert.assertEquals;

import com.gregory.opi.lab7.Point2D;
import com.gregory.opi.lab7.Segment;

import org.junit.Test;

public class AnglesTest {

    private final Point2D ox = new Point2D(0,0);

    @Test
    public void usualLines() {
        Segment s = new Segment();
        s.setP1(ox);

        s.setP2(new Point2D(1, 1));
        assertEquals(Math.PI / 4, s.getAngle(), 0.05);

        s.setP2(new Point2D(1, -1));
        assertEquals(-Math.PI/4, s.getAngle(), 0.05);

        s.setP2(new Point2D(-1, 1));
        assertEquals(Math.PI*3/4,s.getAngle(),0.05);

        s.setP2(new Point2D(-1, -1));
        assertEquals(-Math.PI*3/4, s.getAngle(),0.05);
    }

    @Test
    public void horizontalLines(){
        Segment s;

        s = new Segment(ox, new Point2D(2,0));
        assertEquals(0,s.getAngle(),0.05);

        s = new Segment(ox, new Point2D(-2,0));
        assertEquals(Math.PI, s.getAngle(),0.05);
    }

    @Test
    public void verticalLines() {
        Segment s = new Segment();
        s.setP1(ox);

        s.setP2(new Point2D(0, 200));
        assertEquals(Math.PI / 2, s.getAngle(), 0.05);

        s.setP2(new Point2D(0,-200));
        assertEquals(-Math.PI/2,s.getAngle(),0.05);
    }
}
