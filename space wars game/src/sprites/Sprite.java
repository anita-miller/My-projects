package sprites;

import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;

import main.App;
import utilities.BoundingBox;

public class Sprite{
	private BoundingBox bb;
	private Image image = null;
	private float x;
	private float y;
	private int delay;
	private boolean active = true;
	private boolean visible = false;
	
	/**
     * Constructor.
	 * @param image_src
     * @param x
	 * @param y
	 */	
	public Sprite(String imageSrc, float x, float y, int delay){
		
		try {
			image = new Image(imageSrc);
		} catch (SlickException e) {
			e.printStackTrace();
		}
		
		this.x = x;
		this.y = y;
		this.delay = delay;
		bb = new BoundingBox(image, x, y);
	}

    /**
	 * Runs once every frame.
	 * @param delta
     * @throws SlickException 
	 */
    public void update(Input input, int delta){
    		
	}
	
	/**
	 * Draws the sprite's image.
	 
	 */
	public void render(Graphics g) {
		image.drawCentered(x, y);
	}

	public void contactSprite(Sprite other) {
		
	}

	/*
	 *  Forces the sprite to remain on the screen
	 */
	public void clampToScreen() {
		x = Math.max(x, 0);
		x = Math.min(x, App.SCREEN_WIDTH);
		y = Math.max(y, 0);
		y = Math.min(y, App.SCREEN_HEIGHT);
	}
	
	/*
	 * Returns true whenever the sprite is on screen.
	 */
	public boolean onScreen() {
		return x >= 0 && x <= App.SCREEN_WIDTH - bb.getWidth()
			&& y >= 0 && y <= App.SCREEN_HEIGHT - bb.getHeight();
	}
	
	/**
	 * @return the x
	 */
	public float getX() {
		return x;
	}

	/**
	 * @param x the x to set
	 */
	public void setX(float x) {
		this.x = x;
	}

	/**
	 * @return the y
	 */
	public float getY() {
		return y;
	}
	
	/**
	 * @param y the y to set
	 */
	public void setY(float y) {
		this.y = y;
	}

	/**
	 * @return the delay
	 */
	public int getDelay() {
		return delay;
	}

	
	public boolean getActive() { return active; }
	public void deactivate() { active = false; }
	public void activate() { active = true; }
	
	/**
	 * @return the visible
	 */
	public boolean isVisible() {
		return visible;
	}

	/**
	 * @param visible the visible to set
	 */
	public void setVisible(boolean visible) {
		this.visible = visible;
	}

	/**
	 * @return new bb
	 */
	public BoundingBox getBoundingBox() {
		return new BoundingBox(bb);
	}

	public void move(float dx, float dy) {
		x += dx;
		y += dy;
		bb.setX(x);
		bb.setY(y);
	}

}
