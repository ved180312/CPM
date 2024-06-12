# frozen_string_literal: true
module Slots
  class CreateSlotService
    def initialize(slot_params)
      @slot = Slot.new(slot_params)
    end

    def call
      if @slot.save
        return { success: true, slot: @slot, floor: @slot.floor }
      else
        return { success: false, errors: @slot.errors }
      end
    end
  end
end
