package sprites;


import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;


public class EnemyLaserShot extends Sprite{
	private final float SPEED = 0.7f;
	
    /**
	 * Constructor.
	 * @param x
	 * @param y
	 */
	public EnemyLaserShot(float x, float y, int delay) throws SlickException{
		super("res/enemy-shot.png", x, y, 0);
		}
	
	/**
	 * Runs once every frame.
	 * @param input input the values input by user
	 * @param delta Time passed since last frame (milliseconds).
	 * */
	@Override
	public void update(Input input, int delta) {
		
		if (input.isKeyDown(Input.KEY_S)) {
			//delta=delta*5;
			move(0, SPEED*5);
			
		}
		else {
			move(0, SPEED);
		}
		
	}
	
	/** do appropriate changes when one sprite makes contact with another
     * @param other sprite that contacts 
     */
	@Override
	public void contactSprite(Sprite other) {
		// Check if the enemy made contact with the player
		if (other instanceof Spaceship) {
			//remove a life when player doesnt have a shield or powerup shield
			if(!Spaceship.isShield() && !Spaceship.isPowerupShield()) {
				
				Spaceship.images.remove(Spaceship.images.size()-1);
				//give player shield after contacting laser
				Spaceship.setShield(true);
				
				//if no lives left end the game
				if(Spaceship.images.size() == 0) {
					System.exit(0);
				}
			}
		}		
	}
}
