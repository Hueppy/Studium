package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.vorgaben.graphic.Animation;
import java.util.Arrays;

/** Implementierung des Oger-Monsters. */
public class Ogre extends Monster {
  private static final Animation idle =
      new Animation(
          Arrays.asList(
              new Texture("assets/frames/ogre_idle_anim_f0.png"),
              new Texture("assets/frames/ogre_idle_anim_f1.png"),
              new Texture("assets/frames/ogre_idle_anim_f2.png"),
              new Texture("assets/frames/ogre_idle_anim_f3.png")),
          4);
  private static final Animation walk =
      new Animation(
          Arrays.asList(
              new Texture("assets/frames/ogre_run_anim_f0.png"),
              new Texture("assets/frames/ogre_run_anim_f1.png"),
              new Texture("assets/frames/ogre_run_anim_f2.png"),
              new Texture("assets/frames/ogre_run_anim_f3.png")),
          4);

  public Ogre() {
    super(100, 40);
  }

  @Override
  protected Animation getIdleAnimation() {
    return idle;
  }

  @Override
  protected Animation getWalkAnimation() {
    return walk;
  }
}
