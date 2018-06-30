package sprites;

import java.util.Random;

import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;

import main.World;
import sprites.Sprite;
import sprites.ShieldPowerup;
import utilities.Timer;

public class BasicEnemy extends Sprite{
	private final float SPEED = 0.2f;
	Random rand = new Random();
	
	private Timer appearTimer = new Timer(getDelay());
	
	private boolean shieldPowerup;
	private boolean shotSpeedPowerup;
	/**
	 * Constructor.
	 * @param x
	 * @param y
	 * @param delay
	 */
	public BasicEnemy(float x, float y, int delay) throws SlickException {
		super("res/basic-enemy.png", x, y, delay);
	}

	/** Update the game state for a frame.
     * @param input input the values input by user
     * @param delta Time passed since last frame (milliseconds).
     */
	@Override
	public void update(Input input, int delta) {
		
		//change visibility when delay time is finished
		appearTimer.update(delta);
		if (appearTimer.expired()) {
			setVisible(true);
		}
		
		if(isVisible()) {
			if (input.isKeyDown(Input.KEY_S)) {
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
			Spaceship.setScoreCount(Spaceship.getScoreCount()+50);
			//drop powerup randomly
			if (rand.nextDouble() < 0.025) {
				setShieldPowerup(true);
			}
			else if(rand.nextDouble() < 0.025){
				setShotSpeedPowerup(true);
			 	
			}
			//if not dropping powerup disappear
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