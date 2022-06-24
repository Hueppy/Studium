package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Implementierung eines Waffen-Gegenstandes. */
public abstract class Weapon extends Item {
  private boolean mirrored;

  @Override
  public void draw(float xoffset, float yoffset, float xscaling, float yscaling) {
    final Texture texture = getTexture();
    final float aspect = (float) texture.getWidth() / (float) texture.getHeight();
    final float xScale = Math.copySign(Math.min(aspect, 1f), mirrored ? -1 : 1);
    final float yScale = Math.min(1f / aspect, 1f);
    final float xOff = mirrored ? 0.66f : 0.33f;
    final float yOff = 0f;

    super.draw(
        xOff, yOff,
        xScale, yScale);
  }

  /** Rüstet den übergebenen Helden mit der Waffe aus. */
  @Override
  public void use(Character hero) {
    hero.equip(this);
  }

  public abstract void attack(Point direction);

  public abstract int getAttack();

  public abstract String getWeaponName();

  public boolean isMirrored() {
    return mirrored;
  }

  public void setMirrored(boolean mirrored) {
    this.mirrored = mirrored;
  }

  @Override
  public String toString() {
    return String.format("%s (%d atk)", getWeaponName(), getAttack());
  }
}
