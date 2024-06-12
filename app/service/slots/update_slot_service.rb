# frozen_string_literal: true
module Slots
  class UpdateSlotService
    def initialize(slot, slot_params)
      @slot = slot
      @slot_params = slot_params
    end

    def call
      if @slot.update(@slot_params)
        return { success: true, slot: @slot }
      else
        return { success: false, errors: @slot.errors }
      end
    end
  end
end