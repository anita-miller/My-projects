/**
 * 
 */
package sprites;

import java.util.Random;

import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;

import main.World;
import utilities.Timer;

/**
 * @author anitanaseri
 *
 */
public class SineEnemy extends Sprite{
	public final float AMPLITUDE = 96 ;
	public final double PERIOD_CONSTANT = 1500;
	
	private final float SPEED = 0.15f;
	private Timer timer = new Timer(getDelay());
	private double offSet;
	private int time = 0;
	
	Random rand = new Random();
	private boolean shieldPowerup;
	private boolean shotSpeedPowerup;
	
	//store the original x coordinate
	private float x = getX();
	/**
	 * Constructor.
	 * @param x
	 * @param y
	 * @param delay
	 */
	public SineEnemy(float x, float y, int delay) throws SlickException {
		super("res/sine-enemy.png", x, y, delay);
		
	}
	
	/** Update the game state for a frame.
     * @param input input the values input by user
     * @param delta Time passed since last frame (milliseconds).
     */
	public void update(Input input, int delta) {
		
		//keep tracking of the time that have passed so far in the game
		time += delta;
		//change visibility when delay time is finished
		timer.update(delta);
		if (timer.expired()) {
			setVisible(true);
		}
	
		if(isVisible()) {
			
			//create offset based on time  and assigned delay
			offSet =96*Math.sin(((2*Math.PI)/PERIOD_CONSTANT) *(time-getDelay()));
			
			//add the offset to original x coordinate
			setX(x+(float) offSet);
			
			//move the enemy down the screen with specified speed
			if (input.isKeyDown(Input.KEY_S)) {
				//delta=delta*5;
				move(0, SPEED*5);
				
			}
			else {
				move(0, SPEED);
			}
			
			
		}
		//if after enemy is destroyed, a shot speed powerup appears
		if(isShotSpeedPowerup()) {
			try {
				//replace the enemy sprite with a shot speed powerup sprite
				World.getInstance().replaceSprite(this, new ShotSpeedPowerup(getX(), getY(), 0));
			} catch (SlickException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		//if after enemy is destroyed, a shield powerup appears
		if(isShieldPowerup()) {
			try {
				//replace the enemy sprite with a shield powerup sprite
				World.getInstance().replaceSprite(this, new ShieldPowerup(getX(), getY(), 0));
			} catch (SlickException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	/** do appropriate changes when one sprite makes contact with another
     * @param other sprite that contacts 
     */
	@Override
	public void contactSprite(Sprite other) {
		
		//if contacts laser shot
		if (other instanceof Laser) {
			//add to total score
			Spaceship.setScoreCount(Spaceship.getScoreCount()+100);
			
			//randomly drop powerups
			if (rand.nextDouble() < 0.025) {
				setShieldPowerup(true);
			}
			else if(rand.nextDouble() < 0.025){
				setShotSpeedPowerup(true);
			 	
			}
			else {
				
				 deactivate();
				other.deactivate();
			}
		}
	}

	/**
	 * @return the shieldPowerup
	 */
	public boolean isShieldPowerup() {
		return shieldPowerup;
	}

	/**
	 * @param shieldPowerup the shieldPowerup to set
	 */
	public void setShieldPowerup(boolean shieldPowerup) {
		this.shieldPowerup = shieldPowerup;
	}

	/**
	 * @return the shotSpeedPowerup
	 */
	public boolean isShotSpeedPowerup() {
		return shotSpeedPowerup;
	}

	/**
	 * @param shotSpeedPowerup the shotSpeedPowerup to set
	 */
	public void setShotSpeedPowerup(boolean shotSpeedPowerup) {
		this.shotSpeedPowerup = shotSpeedPowerup;
	}
}
