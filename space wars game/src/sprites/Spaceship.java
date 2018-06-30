/**
 * 
 */
package sprites;

/**
 * @author anitanaseri
 *
 */

import java.util.ArrayList;

import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;
import sprites.Laser;
import main.World;
import utilities.Timer;
 

public class Spaceship extends Sprite{
	private static int scoreCount =0;
	
    public static ArrayList<Image> images = new ArrayList<>();
    private final float SPEED = 0.5f;
    private final static float LIVES_HEIGHT = 696;
    
    private static Timer timer = new Timer(350);
    private static Timer powerupTimer = new Timer(150);
    private Timer shieldTimer = new Timer(3000);
    private Timer powerupEffectTimer = new Timer(5000);
    
    private Image imageLives = null;
    private Image imageShield= null;
    
    private static boolean shield = false;
    private static boolean powerupShield = false;
    private static boolean shotSpeedPowerup = false;
    /**
	 * Constructor.
	 * @param x
	 * @param y
	 */
	public Spaceship(float x, float y) throws SlickException {
		super("res/spaceship.png", x, y, 0);
		
		//create images for lives and shield
		try {
			imageLives = new Image("res/lives.png");
			imageShield = new Image("res/shield.png");
		} catch (SlickException e) {
			e.printStackTrace();
		}
		
		//create 3 live images
		for(int j = 0 ; j<3; j++) {
			images.add(imageLives);
		}
	}
	
	/** Update the game state for a frame.
     * @param input input the values input by user
     * @param delta Time passed since last frame (milliseconds).
     */
	@Override
	public void update(Input input, int delta) {
		
		doMovement(input, delta);
		
		//if player has shield turn it off after 3000 milliseconds
		if(isShield()) {
			shieldTimer.update(delta);
			if (shieldTimer.expired()) {
				setShield(false);
			}
		}
		//after contacting any type of powerup , player's powerup powers will go aways after speficic time
		if(isShotSpeedPowerup() || isPowerupShield()) {
			powerupEffectTimer.update(delta);
			if (powerupEffectTimer.expired()) {
				setPowerupShield(false);
				setShotSpeedPowerup(false);
			}
		}
		
		
		
		
		// do shooting once when space is pressed
		if (input.isKeyPressed(Input.KEY_SPACE)) {
			try {
				World.getInstance().addSprite(new Laser(getX(), getY(), 0));
			} catch (SlickException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		
		if (input.isKeyDown(Input.KEY_SPACE)) {
			//if shot speed powerup is active 
			if(isShotSpeedPowerup()) {
				
				//the time between laser shots is 150 milliseconds
				powerupTimer.update(delta);
				if (powerupTimer.expired()) {
					try {
						World.getInstance().addSprite(new Laser(getX(), getY(), 0));
					} catch (SlickException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}else {
				//if shot speed powerup is inactive, the time between laser shots is 350 milliseconds 
				timer.update(delta);
				if (timer.expired()) {
					try {
						World.getInstance().addSprite(new Laser(getX(), getY(), 0));
					} catch (SlickException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}
	}
	
	/** do appropriate changes when one sprite makes contact with another
     * @param other sprite that contacts 
     */
	@Override
	public void contactSprite(Sprite other) {
		// Check if the player makes contact with the any enemy
		if (other instanceof Sprite && !(other instanceof Laser)) {
			//remove a life when player doesnt have a shield or powerup shield
			if(!isShield() && !isPowerupShield()) {
				images.remove(Spaceship.images.size()-1);
				setShield(true);
				//if no lives left end the game
				if(images.size() == 0) {
					System.exit(0);
				}
			}
		}
		// check if player contacts the  shot speed powerup
		if (other instanceof ShotSpeedPowerup) {
			setShotSpeedPowerup(true);
			other.deactivate();
		}
		// check if player contacts the shield powerup
		if (other instanceof ShieldPowerup) {
			setPowerupShield(true);
			other.deactivate();
		}

	}

	private void doMovement(Input input, int delta) {
		// handle horizontal movement
		float dx = 0;
		if (input.isKeyDown(Input.KEY_LEFT)) {
			dx -= SPEED;
		}
		if (input.isKeyDown(Input.KEY_RIGHT)) {
			dx += SPEED;
		}

		// handle vertical movement
		float dy = 0;
		if (input.isKeyDown(Input.KEY_UP)) {
			dy -= SPEED;
		}
		if (input.isKeyDown(Input.KEY_DOWN)) {
			dy += SPEED;
		}
		
		move(dx * delta, dy * delta);
		clampToScreen();
	}

	/* (non-Javadoc)
	 * @see sprites.Sprite#render()
	 */
	@Override
	public void render(Graphics g) {
		//System.out.println(images.size());
		for(int j = 0 ; j<images.size(); j++) {
			for(int i = 40; i <= images.size()*40; i=i+40) {
				imageLives.drawCentered(i, LIVES_HEIGHT);
			}
		}
		if(isShield() ) {
			imageShield.drawCentered(getX(), getY());
		}
		
		//when contacts powerup shield spaceship gets a shield
		if(isPowerupShield() ) {
			imageShield.drawCentered(getX(), getY());
		}
		
		//adding the score
		g.drawString("Score: " + scoreCount , 20, 738);
		super.render(g);
	}

	/**
	 * @return the scoreCount
	 */
	public static int getScoreCount() {
		return scoreCount;
	}

	/**
	 * @param scoreCount the scoreCount to set
	 */
	public static void setScoreCount(int scoreCount) {
		Spaceship.scoreCount = scoreCount;
	}

	/**
	 * @return the shield
	 */
	public static boolean isShield() {
		return shield;
	}

	/**
	 * @param shield the shield to set
	 */
	public static void setShield(boolean shield) {
		Spaceship.shield = shield;
	}

	/**
	 * @return the powerupShield
	 */
	public static boolean isPowerupShield() {
		return powerupShield;
	}

	/**
	 * @param powerupShield the powerupShield to set
	 */
	public static void setPowerupShield(boolean powerupShield) {
		Spaceship.powerupShield = powerupShield;
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
		Spaceship.shotSpeedPowerup = shotSpeedPowerup;
	}


}
