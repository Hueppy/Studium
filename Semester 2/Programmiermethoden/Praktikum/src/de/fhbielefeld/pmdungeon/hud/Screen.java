package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import de.fhbielefeld.pmdungeon.vorgaben.graphic.TextStage;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Constants;

/** Abstrakte Basisklasse für eine "Bildschirm"-Darstellung. */
public abstract class Screen<T> {
  protected final OrthographicCamera camera;
  protected final SpriteBatch batch;
  protected final TextStage textStage;

  /** Erstellt eine neue "Bildschirm"-Darstellung. */
  public Screen() {
    this.batch = new SpriteBatch();
    this.textStage = new TextStage(this.batch);
    camera = new OrthographicCamera();
    camera.position.set(0, 0, 0);
    camera.update();
  }

  protected abstract Texture getBackground();

  protected abstract void drawContents(T object);

  protected Label createLabel(int x, int y) {
    return textStage.drawText(
        "", "assets/fonts/Minecraftia-Regular.ttf", Color.WHITE, 16, 100, 10, x, y);
  }

  /** Stellt das übergebene Objekt auf dem Bildschirm dar. */
  public void show(T object) {
    camera.update();
    batch.setProjectionMatrix(camera.combined);

    Texture bg = getBackground();
    if (bg != null) {
      Sprite background = new Sprite(bg);
      background.setPosition(0.5f, 1.75f);
      background.setSize(5.5f, 2f);

      batch.begin();
      background.draw(batch);
      batch.end();
    }

    batch.begin();
    drawContents(object);
    batch.end();

    textStage.draw();

    camera.setToOrtho(
        false,
        Constants.VIRTUALHEIGHT * Constants.WIDTH / (float) Constants.HEIGHT,
        Constants.VIRTUALHEIGHT);
  }
}
