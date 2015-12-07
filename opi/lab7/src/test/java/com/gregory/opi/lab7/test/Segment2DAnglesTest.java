package com.gregory.opi.lab7.test;

import com.gregory.opi.lab7.Point2D;
import com.gregory.opi.lab7.Segment2D;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class Segment2DAnglesTest {

    private final Point2D ox = new Point2D(0, 0);

    @Test
    public void usualLines() {
        Segment2D s = new Segment2D();
        s.setP1(ox);

        s.setP2(new Point2D(1, 1));
        assertEquals(Math.PI / 4, s.getAngle(), 0.05);

        s.setP2(new Point2D(1, -1));
        assertEquals(-Math.PI / 4, s.getAngle(), 0.05);

        s.setP2(new Point2D(-1, 1));
        assertEquals(Math.PI * 3 / 4, s.getAngle(), 0.05);

        s.setP2(new Point2D(-1, -1));
        assertEquals(-Math.PI * 3 / 4, s.getAngle(), 0.05);
    }

    @Test
    public void horizontalLines() {
        Segment2D s;

        s = new Segment2D(ox, new Point2D(2, 0));
        assertEquals(0, s.getAngle(), 0.05);

        s = new Segment2D(ox, new Point2D(-2, 0));
        assertEquals(Math.PI, s.getAngle(), 0.05);
    }

    @Test
    public void verticalLines() {
        Segment2D s = new Segment2D();
        s.setP1(ox);

        s.setP2(new Point2D(0, 200));
        assertEquals(Math.PI / 2, s.getAngle(), 0.05);

        s.setP2(new Point2D(0, -200));
        assertEquals(-Math.PI / 2, s.getAngle(), 0.05);
    }
}
