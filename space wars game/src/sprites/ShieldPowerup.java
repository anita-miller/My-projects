package sprites;

import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;


public class ShieldPowerup extends Sprite{
	private final float SPEED = 0.1f;
	
	/**
	 * Constructor.
	 * @param x
	 * @param y
	 * @param delay
	 */
	public ShieldPowerup(float x, float y, int delay) throws SlickException {
		super("res/shield-powerup.png", x, y, delay);
		
	}
	
	/** Update the game state for a frame.
     * @param input input the values input by user
     * @param delta Time passed since last frame (milliseconds).
     */
	public void update(Input input, int delta) {
		
		if (input.isKeyDown(Input.KEY_S)) {
			//delta=delta*5;
			move(0, SPEED*5);
			
		}
		else {
			move(0, SPEED);
		}
		
		if (!onScreen()) {
			deactivate();
		}
	}

}
