package sprites;


import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;


public class Laser extends Sprite{
	private final float SPEED = 3;
	
	
    /**
	 * Constructor.
	 * @param x
	 * @param y
     * @throws SlickException 
	 */
	public Laser(float x, float y, int delay) throws SlickException{
		super("res/shot.png", x, y, 0);
	}
	
	/**
	 * Runs once every frame.
	 * @param input input the values input by user
	 * @param delta Time passed since last frame (milliseconds).
	 * */
	@Override
	public void update(Input input, int delta) {
		
		//move up the screen
		if (input.isKeyDown(Input.KEY_S)) {
			move(0, -SPEED*5);
		}
		else {
			move(0, -SPEED);
		}
		
		if (!onScreen()) {
			deactivate();
		}
	}	
}
