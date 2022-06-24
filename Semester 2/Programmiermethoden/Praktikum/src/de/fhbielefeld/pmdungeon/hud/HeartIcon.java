package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IHUDElement;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Lebensanzeige. */
public class HeartIcon implements IHUDElement {
  private static final Texture empty = new Texture("assets/frames/ui_heart_empty.png");
  private static final Texture half = new Texture("assets/frames/ui_heart_half.png");
  private static final Texture full = new Texture("assets/frames/ui_heart_full.png");

  private final Point position;
  private final int num;
  private final Hero hero;

  /** Erstellt ein neues Icon der Lebensanzeige. */
  public HeartIcon(int num, Hero hero) {
    this.num = num;
    this.position = new Point(0.5f * (num + 1), 4.5f);
    this.hero = hero;
  }

  @Override
  public Point getPosition() {
    return position;
  }

  @Override
  public Texture getTexture() {
    final int health = Math.max(hero.getHealth() - num * 100, 0);

    if (health > 50) {
      return full;
    } else if (health > 0) {
      return half;
    }

    return empty;
  }
}
