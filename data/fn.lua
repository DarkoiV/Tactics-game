Fn = {
	-- Wait for x frames
	wait = function (frames)
		for _ = 1, frames do
			coroutine.yield()
		end
	end,
}
