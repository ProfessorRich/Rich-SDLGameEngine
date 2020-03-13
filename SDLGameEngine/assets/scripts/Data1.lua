Data1 = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="texture", id = "flame-texture", file = "./assets/images/flame-basic.png" },
	    [1] = { type="font", id = "normal", file = "./assets/fonts/sitka.ttc", fontSize = 14 },
        [2] = { type="font", id = "system", file = "./assets/fonts/system.fon", fontSize = 24 },
        [3] = { type="texture", id = "terrain-texture", file = "./assets/tilemaps/jungle.png" }
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = "terrain-texture",
        file = "./assets/tilemaps/jungle.map",
        scale = 3,
        tileSize = 32,
        mapSizeX = 25,
        mapSizeY = 20
    },

    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] = {
            name = "flame",
            layer = 6,
            components = {
                transform = {
                    position = {
                        x = 0,
                        y = 900-64
                    },
                    velocity = {
                        x = 0,
                        y = 0
					},
                    width = 64,
                    height = 64,
                    scale = 1,
                    rotation = 0
				},
                sprite = {
                    textureAssetId = "flame-texture",
                    animated = true, 
                    frameCount = 2,
                    animationSpeed = 3,
                    fixed = true
				}
			}
		}
        
    }
}
