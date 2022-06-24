package de.fhbielefeld.pmdungeon.entities.traps;

import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.entities.Character;
import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.entities.Monster;
import de.fhbielefeld.pmdungeon.entities.Ogre;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.Random;
import java.util.function.Consumer;

/** Falle die bei Berührung mehrere Monster herbeiruft. */
public class SpawnTrap extends Trap {
  private static final Texture texture = new Texture("assets/frames/trap_spawner.png");
  private static final Texture invisible = new Texture(0, 0, Pixmap.Format.Alpha);
  private static final Random random = new Random();
  private final Hero hero;
  private final Consumer<Monster> spawn;
  private boolean activated;

  public SpawnTrap(Hero hero, Consumer<Monster> spawn) {
    this.hero = hero;
    this.spawn = spawn;
  }

  @Override
  public void activate(Character character) {
    if (!activated && character instanceof Hero) {
      final Point position = getPosition();
      for (int i = 0; i < 3; i++) {
        final Ogre ogre = new Ogre();
        spawn.accept(ogre);
        ogre.setPosition(
            new Point(
                position.x + random.nextFloat() - 0.5f, position.y + random.nextFloat() - 0.5f));
      }
      activated = true;
    }
  }

  @Override
  public Texture getTexture() {
    if (hero.isVisible()) {
      return invisible;
    } else {
      return texture;
    }
  }

  @Override
  public boolean deleteable() {
    return activated;
  }
}
