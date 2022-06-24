package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IHUDElement;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.nio.file.Path;

/** Erfahrungsanzeige. */
public class LevelProgressFragment implements IHUDElement {
  private final Type type;
  private final Point position;
  private final Hero hero;
  private final int num;

  /** Erstellt ein neues Fragment der Erfahrungsanzeige. */
  public LevelProgressFragment(Hero hero, int num, Type type) {
    this.hero = hero;
    this.num = num;
    this.type = type;
    this.position = new Point(0.5f + (num * 0.25f), 4.35f);
  }

  @Override
  public Point getPosition() {
    return position;
  }

  @Override
  public Texture getTexture() {
    final int xp = Math.max(this.hero.getExperience() - num * 10, 0);

    if (xp >= 10) {
      return type.full;
    } else {
      return type.empty;
    }
  }

  @Override
  public float getHeight() {
    return getTexture().getWidth() / 6;
  }

  @Override
  public float getWidth() {
    return 0.25f;
  }

  /** Typ des Fragments, Start-, Mittel- oder Endfragment. */
  public enum Type {
    Start("ui_xp_full_start.png", "ui_xp_empty_start.png"),
    Middle("ui_xp_full.png", "ui_xp_empty.png"),
    End("ui_xp_full_end.png", "ui_xp_empty_end.png");

    public final Texture full;
    public final Texture empty;

    Type(String full, String empty) {
      this.full = new Texture(Path.of("assets\\frames", full).toString());
      this.empty = new Texture(Path.of("assets\\frames", empty).toString());
    }
  }
}
