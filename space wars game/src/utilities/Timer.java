package utilities;

public class Timer {
	private int time = 0;
	private int target;
	
	/**
	 * Constructor.
	 * @param milliseconds
	 */
	public Timer(int milliseconds) {
		target = milliseconds;
	}
	
	/**
	 * Updates the counter on the time.
	 * @param delta
	 */
	public void update(int delta) {
		time += delta;
	}
	
	/**
	 * Returns true if the timer has been set off, and also resets the time.
	 * @return
	 */
	public boolean expired() {
		if (time >= target) {
			time = 0;
			return true;
		}
		return false;
	}
}
