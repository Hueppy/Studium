package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.vorgaben.graphic.Animation;
import java.util.Arrays;

/** Implementierung des Mimic-Truhen-Monster. */
public class MimicChest extends Monster {
  private static final Animation animation =
      new Animation(
          Arrays.asList(
              new Texture("assets/frames/chest_mimic_open_anim_f0.png"),
              new Texture("assets/frames/chest_mimic_open_anim_f1.png"),
              new Texture("assets/frames/chest_mimic_open_anim_f2.png")),
          8);

  public MimicChest() {
    super(99, 20);
  }

  @Override
  protected Animation getIdleAnimation() {
    return animation;
  }

  @Override
  protected Animation getWalkAnimation() {
    return animation;
  }
}
