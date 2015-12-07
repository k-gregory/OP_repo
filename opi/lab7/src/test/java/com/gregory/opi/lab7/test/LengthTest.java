package com.gregory.opi.lab7.test;

import com.gregory.opi.lab7.Point2D;
import com.gregory.opi.lab7.Segment2D;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * Created by gregory on 07.12.15.
 */
public class LengthTest {

    private final Point2D ox = new Point2D(0, 0);

    @Test
    public void simpleLengthToOX() {
        Segment2D s = new Segment2D();
        s.setP1(ox);

        s.setP2(new Point2D(0, 1));
        assertEquals(1, s.getLength(), 0.001);

        s.setP2(new Point2D(1, 1));
        assertEquals(Math.sqrt(2), s.getLength(), 0.001);
    }

    @Test
    public void simpleLengthTest() {
        Segment2D s = new Segment2D();
        s.setP1(new Point2D(3, 4));

        s.setP2(new Point2D(3, 5));
        assertEquals(1, s.getLength(), 0.001);

        s.setP2(new Point2D(4, 7));
        assertEquals(Math.sqrt(10), s.getLength(), 0.001);
    }

    @Test
    public void lengthCommutativity() {
        for (int i = -5000; i < 5000; i += 500) {
            Point2D p1 = new Point2D(i, i);
            Point2D p2 = new Point2D(i + 10, i - 10);
            assertEquals(new Segment2D(p1, p2).getLength(), new Segment2D(p2, p1).getLength(), 0.001);
        }
    }
}
