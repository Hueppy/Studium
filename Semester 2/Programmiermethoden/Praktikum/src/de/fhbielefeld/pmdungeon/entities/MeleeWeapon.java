package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Nahkampfwaffe. */
public class MeleeWeapon extends Weapon {
  private final Type type;

  /** Erstellt eine neue Nahkampfwaffe mit dem übergebenen Typen. */
  public MeleeWeapon(Type type) {
    this.type = type;
  }

  @Override
  protected Texture createTexture() {
    switch (this.type) {
      case Cleaver:
        return new Texture("assets/frames/weapon_cleaver.png");
      default:
        return null;
    }
  }

  @Override
  public void attack(Point direction) {}

  /** Gibt die Angriffpunkte der Waffe zurück. */
  @Override
  public int getAttack() {
    switch (this.type) {
      case Cleaver:
        return 100;
      default:
        return 0;
    }
  }

  /** Gibt den Namen der Waffe zurück. */
  public String getWeaponName() {
    switch (type) {
      case Cleaver:
        return "Cleaver";
      default:
        return "";
    }
  }

  /** Typ der Waffe. */
  public enum Type {
    Cleaver
  }
}
