# frozen_string_literal: true

class AddSlotIdToCustomerDetails < ActiveRecord::Migration[7.0]
  def change
    add_column :customer_details, :slot_id, :integer
  end
end
