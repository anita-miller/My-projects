/**
 * 
 */
package sprites;

import java.util.Random;

import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;

import main.World;
import utilities.Timer;

public class Boss extends Sprite{
	
	private Timer appearTimer = new Timer(getDelay());
	private Timer firstTimer = new Timer(5000);
	private Timer secondTimer = new Timer(2000);
	private Timer shootingTimer = new Timer(200);
	private Timer lastTimer = new Timer(3000);
	
	private boolean firstAppear = false;
	private boolean secondAppear = false;
	private boolean startShooting = true;
	
	private final float BOSS_FIRST_SPEED = 0.05f;
	private final float BOSS_SECOND_SPEED = 0.2f;
	private final float BOSS_THIRD_SPEED = 0.1f;
	private final float START = 72;
	private final int MIN = 128;
	private final int MAX = 896;
	
	private final int FIRST_OFFSET = -97;
	private final int SECOND_OFFSET = -74;
	private final int THIRD_OFFSET = 97;
	private final int FOURTH_OFFSET = 74;
	
	private float countLaserShots = 0;
	
	Random rand = new Random();
	private int firstRandom; 
	private int secondRandom;
	
	

	/**
	 * Constructor.
	 * @param x
	 * @param y
	 * @param delay
	 */
	public Boss(float x, float y, int delay) throws SlickException {
		super("res/boss.png", x, y, delay);
		firstRandom = (int) (MIN + rand.nextFloat() * (MAX - MIN));
		secondRandom = (int) (MIN + rand.nextFloat() * (MAX - MIN));
		//deactivate();
	}

	public void update(Input input, int delta) {
		
		//change visibility when delay time is finished
		appearTimer.update(delta);
		if (appearTimer.expired()) {
			
			setVisible(true);
		}
		if(isVisible()) {
			// if y coordinate is less than 72 move down the screen 
			if(getY() < START) {
				if (input.isKeyDown(Input.KEY_S)) {
					move(0, BOSS_FIRST_SPEED*5);	
				}
				else {
					move(0, BOSS_FIRST_SPEED);	
				}
				
			}
			else {
				//check if its second movement or first movement's turn
				if(!isSecondAppear()) {
					//wait 5000miliseconds then activate the first movement
					firstTimer.update(delta);
					if (firstTimer.expired()) {
						setFirstAppear(true);
					}
				}
				
				if(isFirstAppear()) {
					//if random x is lower that the current postion move to left towards it 
					if(getX() > firstRandom) {
						
						if (input.isKeyDown(Input.KEY_S)) {
							move(-BOSS_SECOND_SPEED*5, 0);	
						}
						else {
							move(-BOSS_SECOND_SPEED, 0);	
						}
					}
					//if random x is higher that the current postion move to right towards it 
					else {
						if (input.isKeyDown(Input.KEY_S)) {
							move(BOSS_SECOND_SPEED*5, 0);	
						}
						else {
							move(BOSS_SECOND_SPEED, 0);	
						}
					}
					
					//when at the random x coordinate 
					if(Math.abs(getX() - firstRandom) < 0.1) {
						
						// wait 2000 miliseconds, deactivate first movement and activate second movement
						secondTimer.update(delta);
						if (secondTimer.expired()) {
							setSecondAppear(true);
							setFirstAppear(false);
						}
					}
				}
				
				//start moving towards second random number
				if(isSecondAppear()){
					
					//if random x is higher that the current postion move to right towards it 
					if(secondRandom > firstRandom ) {
						if (input.isKeyDown(Input.KEY_S)) {
							move(BOSS_THIRD_SPEED*5, 0);	
						}
						else {
							move(BOSS_THIRD_SPEED, 0);	
						}
					}
					//if random x is lower that the current postion move to left towards it 
					else {
						if (input.isKeyDown(Input.KEY_S)) {
							move(-BOSS_THIRD_SPEED*5, 0);	
						}
						else {
							move(-BOSS_THIRD_SPEED, 0);
						}
					}
					
					shootingTimer.update(delta);
					if (shootingTimer.expired()) {
						
							try {
								World.getInstance().addSprite(new EnemyLaserShot(getX() + FIRST_OFFSET, getY(), 0));
								World.getInstance().addSprite(new EnemyLaserShot(getX() + SECOND_OFFSET, getY(), 0));
								World.getInstance().addSprite(new EnemyLaserShot(getX() + THIRD_OFFSET, getY(), 0));
								World.getInstance().addSprite(new EnemyLaserShot(getX() + FOURTH_OFFSET, getY(), 0));
							} catch (SlickException e) {	
								e.printStackTrace();
							}
					}
					
					if(Math.abs(getX() - secondRandom) < 0.1) {
						
						//if random x is higher that the current postion move to right towards it 
						if(secondRandom > firstRandom ) {
							if (input.isKeyDown(Input.KEY_S)) {
								move(-BOSS_THIRD_SPEED*5, 0);	
							}
							else {
								move(-BOSS_THIRD_SPEED, 0);	
							}
						}
						//if random x is lower that the current postion move to left towards it 
						else {
							if (input.isKeyDown(Input.KEY_S)) {
								move(BOSS_THIRD_SPEED*5, 0);	
							}
							else {
								move(BOSS_THIRD_SPEED, 0);	
							}
						}
						
						//continue shooting for 3000millseconds 
						lastTimer.update(delta);
						if (lastTimer.expired()) {
							//choose new random numbers
							firstRandom = (int) (MIN + rand.nextFloat() * (MAX - MIN));
							secondRandom = (int) (MIN + rand.nextFloat() * (MAX - MIN));
							//deactivate second movement and start again
							setSecondAppear(false);
						}
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
		
		// Check if the enemy made contact with laser and deactivate after 60 shots
		if(isVisible()) {
			
			////if contacts laser shot
			if (other instanceof Laser) {
				countLaserShots++;
				
				//be destroyed and add to total score after 60 shots
				if(countLaserShots == 60) {
					Spaceship.setScoreCount(Spaceship.getScoreCount()+5000);
					deactivate();
					other.deactivate();
				}
			}
		}
	}

	/**
	 * @return the firstAppear
	 */
	public boolean isFirstAppear() {
		return firstAppear;
	}

	/**
	 * @param firstAppear the firstAppear to set
	 */
	public void setFirstAppear(boolean firstAppear) {
		this.firstAppear = firstAppear;
	}

	/**
	 * @return the secondAppear
	 */
	public boolean isSecondAppear() {
		return secondAppear;
	}

	/**
	 * @param secondAppear the secondAppear to set
	 */
	public void setSecondAppear(boolean secondAppear) {
		this.secondAppear = secondAppear;
	}

	/**
	 * @return the startShooting
	 */
	public boolean isStartShooting() {
		return startShooting;
	}

	/**
	 * @param startShooting the startShooting to set
	 */
	public void setStartShooting(boolean startShooting) {
		this.startShooting = startShooting;
	}

}
