-------------------------------------------------
-- example.lua
--
-- I can add comments here...
-------------------------------------------------
return {

  app = {
		name = "posh"
	, proper_name = "posh"
	}

, identifier = "ironhead"

	-- List any dependencies here.
, dependencies = {
    { dep = 'com.android.volley:volley:1.1.1' }
  -- { dep = 'androidx.legacy:legacy-support-v4:1.0.0' }
	}

	-- TODO: The templating engine needs to be more flexible.
	-- In lieu of that, I can specify the names of each activity
	-- here so that the manifest will know what do.
,	manifest = {
		activities = {
			{ name = "main" }
		}
	}

	-- List of activities / storyboards and their layouts (if any)
, activities = {
	-- By default, we'll ship with a main activity
		main = {
			name = "main"
		, template = "generic"
		, layout = {
				layout = "linear"
			, elements = {
					main_text = { typ = "TextView", text = "Hello, world" }
				}
			}
		}
	
	--[[
	-- Here's an example of a login activity...
		login = { 
			name = "login"
		, template = "login"
		, layout = {
				layout = "frame"
			,	elements = {
					id1 = {
						typ = "button"
					,	text = "Some text"
					}
				,	id2 = {
						typ = "EditText"
					,	hint = "A hint"
					}
				,	id2 = {
						typ = "EditText"
					,	hint = "Password"
					}
				}	
			}
		}
	--]]
	}
	
	-- Database
, database = {
		-- If you could specify how to create your tables from here that would be 
		-- really cool... and probably save some time...
	}

	-- Specify the fonts you want to add to the font/ directory
, fonts = {

	}

  -- Finally, specify the assets that you need to add... (images, audio, etc)
, assets = {

	}

	-- You should also do other resource things here... like classes, etc.
, classes = {

	}
}
