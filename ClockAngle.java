import java.lang.Math;
import java.time.LocalTime;
import java.time.ZoneId;

/* Question:
 * Given a time, what is the angle formed by the two clock hands
 */

public class ClockAngle {
    /*
     * Returns the smaller angle (in degrees) between the hour-hand
     * and the minute-hand of a clock given a specific time.
     * Example: 12:00 should return 0
     *          6:00 should return 180
     *          3:15 should return 7 (7.5 as an integer)
     */
    static int getAngle(int hour, int minutes) {
        int angle = java.lang.Math.abs((((hour % 12) * 30) + ((30*minutes/60))) - minutes * 6);
        return java.lang.Math.min(angle, 360-angle);
    }

    public static void main(String[] args) {
        ZoneId EST = ZoneId.of("America/New_York");
        LocalTime now = LocalTime.now(EST);
        System.out.println("The Angle of The Current Time (EST) is: " +
                           getAngle(now.getHour(), now.getMinute()) + "°");
    }

}
