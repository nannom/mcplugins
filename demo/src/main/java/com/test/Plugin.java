package com.test;

import java.util.logging.Logger;
import org.bukkit.plugin.java.JavaPlugin;

/*
 * demo java plugin
 */
public class Plugin extends JavaPlugin
{
  private static final Logger LOGGER=Logger.getLogger("demo");

  public void onEnable()
  {
    LOGGER.info("demo enabled");
  }

  public void onDisable()
  {
    LOGGER.info("demo disabled");
  }
  @EventHandler
  public void playerevent(PlayerEvent e) {
    
  }
}
